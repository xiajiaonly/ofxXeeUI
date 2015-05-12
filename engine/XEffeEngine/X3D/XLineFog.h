#ifndef _JIA_XLINEFOG_
#define _JIA_XLINEFOG_

namespace XE{
class XLineFog
{
private:
	unsigned int m_fogMode;
	float m_color[4];
	float m_density;
	float m_start;
	float m_end;
public:
	XLineFog()
		:m_fogMode(GL_FOG)
		,m_density(0.001f)
		,m_start(1.0f)
		,m_end(1000.0f)
	{
		m_color[0] = 0.8f;
		m_color[1] = 0.8f;
		m_color[2] = 0.8f;
		m_color[3] = 1.0f;
	}
	void setColor(float r,float g,float b,float a)
	{
		m_color[0] = r;
		m_color[1] = g;
		m_color[2] = b;
		m_color[3] = a;
	}
	void setColor(const XFColor &color) {setColor(color.fR,color.fG,color.fB,color.fA);}
	void setDensity(float density){m_density = density;}
	void setArea(float start,float end){m_start = start;m_end = end;}
	void useFog()
	{
		glEnable(GL_FOG);
		glFogi(GL_FOG_MODE,GL_EXP);
		glFogfv(GL_FOG_COLOR,m_color);
		glFogf(GL_FOG_DENSITY,m_density);
		glFogf(GL_FOG_START,m_start);
		glFogf(GL_FOG_END,m_end);
		glHint(GL_FOG_HINT,GL_NICEST);
	}
	void disFog(){glDisable(GL_FOG);}
};
}
#endif