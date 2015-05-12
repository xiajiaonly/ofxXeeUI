#version 120

uniform sampler2D Texture;			//��ɫ��ͼ
uniform sampler2D normalTexture;	//������ͼ
uniform sampler2D ShadowMap;		//�����ͼ
uniform int withTex;				//��ǰ�Ƿ�ʹ����ͼ

varying vec4 ShadowMapTexCoord;		//�����ͼ������
varying vec3 Normal;
varying vec3 LightDirection;	//���ߺ͹�ķ���

varying vec3 lightDir;
varying vec3 viewDir;

vec2 poissonDisk[4] = vec2[](
	  vec2( -0.94201624, -0.39906216 ),
	  vec2( 0.94558609, -0.76890725 ),
	  vec2( -0.094184101, -0.92938870 ),
	  vec2( 0.34495938, 0.29387760 ));
void main()
{
	float LightDistance2 = dot(LightDirection,LightDirection);	//��ǰ�����ľ����ƽ��
	float LightDistance = sqrt(LightDistance2);					//��ǰ������ߵľ���
	float NdotLD = max(dot(normalize(Normal), LightDirection / LightDistance), 0.0);	//��������ܹ��ǿ��
	float Attenuation = gl_LightSource[1].constantAttenuation;
	Attenuation += gl_LightSource[1].linearAttenuation * LightDistance;
	Attenuation += gl_LightSource[1].quadraticAttenuation * LightDistance2;
	
	//NdotLD *= shadow2DProj(ShadowMap, ShadowMapTexCoord).r;

	float cosTheta = dot(normalize(Normal),LightDirection);
	float bias = 0.005*tan(acos(cosTheta)); // cosTheta is dot( n,l ), clamped between 0 and 1
	bias = clamp(bias, 0,0.01);

	if(ShadowMapTexCoord.w > 0.0)
	{//ʲô���壿
		vec3 ShadowMapTexCoordProj = ShadowMapTexCoord.xyz / ShadowMapTexCoord.w;
		
		if(ShadowMapTexCoordProj.x >= 0.0 && ShadowMapTexCoordProj.x < 1.0 &&
		   ShadowMapTexCoordProj.y >= 0.0 && ShadowMapTexCoordProj.y < 1.0 &&
		   ShadowMapTexCoordProj.z >= 0.0 && ShadowMapTexCoordProj.z < 1.0)
		{//�����ͼ�ķ�Χ��
			//if(texture2D(ShadowMap,ShadowMapTexCoordProj.xy).r <= ShadowMapTexCoordProj.z)
			if(texture2D(ShadowMap,ShadowMapTexCoordProj.xy).r  <  ShadowMapTexCoordProj.z - bias)
			{//�����ǲ�����Ӱ
				for(int i=0;i<4;i++)
				{
					if(texture2D(ShadowMap,ShadowMapTexCoordProj.xy + poissonDisk[i] / 1024.0).z <  ShadowMapTexCoordProj.z - bias)
					//if(texture2D(ShadowMap,ShadowMapTexCoordProj.xy + poissonDisk[i] / 1024.0).z <=  ShadowMapTexCoordProj.z)
						NdotLD -= 0.2;
				}
			}
			if(NdotLD < 0.0) NdotLD = 0.0;
		}
	}

	vec3 l = lightDir;	//=0
    float atten = max(0.0, 1.0 - dot(l, l));
    atten = 1.0;

    l = normalize(l);

	vec3 n = normalize(texture2D(normalTexture,gl_TexCoord[0].st).rgb * 2.0 - 1.0);
	vec3 v = normalize(viewDir);	//=0
	vec3 h = normalize(l + v);		//=0

	float nDotL = max(0.0, dot(n, l));
	float nDotH = max(0.0, dot(n, h));
	//float power = (nDotL == 0.0) ? 0.0 : pow(nDotH, gl_FrontMaterial.shininess);
	float power = (nDotL == 0.0) ? 0.0 : nDotH;

	vec4 ambient = gl_FrontLightProduct[1].ambient * atten;
	vec4 diffuse = gl_FrontLightProduct[1].diffuse * nDotL * atten;
	vec4 specular = gl_FrontLightProduct[1].specular * power * atten;
	vec4 color = gl_FrontLightModelProduct.sceneColor + ambient + diffuse + specular;
	
	gl_FragColor = gl_Color;
	if(withTex != 0) gl_FragColor *= texture2D(Texture,gl_TexCoord[0].st) * color;
	gl_FragColor.rgb *= (gl_LightSource[1].ambient.rgb + gl_LightSource[1].diffuse.rgb * NdotLD) / Attenuation;

}
