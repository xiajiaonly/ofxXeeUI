#ifndef _JIA_X3DWORLD_
#define _JIA_X3DWORLD_

#include "XBasic3D.h"
#include "XLight.h"
#include "XLineFog.h"
#include "XMaterial.h"
#include "XSkyBox.h"
#include "XModelObj.h"
#include "XModelStl.h"
#include "XCam.h"
#include "XTerrain.h"
#include "XInputEventCommon.h"
#include "XShadowMap.h"
#include "XArcBall.h"
#include "XBasicModel.h"
namespace XE{

enum XWorldShaderType
{
	SHADER_DUMP,
	SHADER_SHADOW,
	SHADER_DUMP_AND_SHADOW,
};
class X3DWorld
{
	friend XShadowMap;
protected:
	X3DWorld()
		:m_isInited(XFalse)
		,m_drawFun(NULL)

		,m_curShader(NULL)
		,m_withDumpMap(XFalse)
		,m_isMouseBtnDown(XFalse)
		,m_targetObj(NULL)
		,m_withSkyBox(XTrue)
		,m_withLight(XTrue)
		,m_withFog(XTrue)
		,m_3dDrawMode(DRAW_MODE_POINT)
	{}
	X3DWorld(const X3DWorld&);
	X3DWorld &operator= (const X3DWorld&);
	virtual ~X3DWorld(){}
public:
	static X3DWorld& GetInstance()
	{
		static X3DWorld m_instance;
		return m_instance;
	}
private:
	XBool m_isInited;

	XKeyState m_keyUpState;
	XKeyState m_keyDownState;
	XKeyState m_keyAState;
	XKeyState m_keyDState;
	XKeyState m_keyWState;
	XKeyState m_keySState;
	XBool m_isMouseBtnDown;

	XBasic3DObject * m_targetObj;

	XShadowMap m_shadowMap;
	XMatrix4x4 m_shadowMatrix;

	XBool m_withShadow;
	unsigned int m_shadowMapTexture;
	XShaderGLSL m_shadowMapShader;
	int m_drawWithTexture;

	XShaderGLSL m_dumpMapShader;
	XBool m_withDumpMap;
	unsigned int m_dumpMapTexture;

	XShaderGLSL *m_curShader;

	XShaderGLSL m_DMapAndSMapGLSL;

	void (*m_drawFun)(XBool withTexture);

	XMatrix3x3 m_mouseRotateMatrixO;
	XMatrix3x3 m_mouseRotateMatrixN;

	XArcBall m_mouseArcBall;

	XBool m_withSkyBox;
	XBool m_withLight;
	XBool m_withFog;

	X3DDrawMode m_3dDrawMode;
public:
	void setUseSkyBox(XBool flag){m_withSkyBox = flag;}
	void setUseLight(XBool flag)
	{
		m_withLight = flag;
		if(m_withLight) m_worldLight.useLight();
		else m_worldLight.disAllLight();
	}
	void setUseFog(XBool flag)
	{
		m_withFog = flag;
		if(m_withFog) m_worldLineFog.useFog();
		else m_worldLineFog.disFog();
	}
	void set3DDrawMode(X3DDrawMode mode)
	{
		m_3dDrawMode = mode;
		switch(m_3dDrawMode)
		{
		case DRAW_MODE_FILL:
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			glEnable(GL_DEPTH_TEST);
			glEnable(GL_CULL_FACE);
			break;
		case DRAW_MODE_LINE:
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			glDisable(GL_DEPTH_TEST);
			glDisable(GL_CULL_FACE);
			break;
		case DRAW_MODE_POINT:
			glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
			glDisable(GL_DEPTH_TEST);
			glDisable(GL_CULL_FACE);
			break;
		}
	}
public:
	XSkyBox m_skyBox;
	XCamRoam m_worldCam;
	XLight m_worldLight;
	XMaterial m_worldMaterial;
	XLineFog m_worldLineFog;
	void useShadow(XBool withTexture,XWorldShaderType type = SHADER_SHADOW,unsigned int dumpTex = 0);
	void removeShadow();

	XVector3 worldToScreen(const XVector3 &point,const XRect &view);
	void setTargetObj(XBasic3DObject * obj){m_targetObj = obj;}

	XBool init(void (* drawFun)(XBool),XResourcePosition resourcePosition = RESOURCE_SYSTEM_DEFINE);
	void draw();
	void move(int stepTime);
	void setWithShadow(XBool flag){m_withShadow = flag;}
	void setWithDumpMap(XBool flag){m_withDumpMap = flag;}
	XBool getWithShadow()const{return m_withShadow;}
	void keyEvent(const XInputEvent& inputEvent);
};
namespace X3D
{
	extern void addCameraToCFG();
}
}
#endif