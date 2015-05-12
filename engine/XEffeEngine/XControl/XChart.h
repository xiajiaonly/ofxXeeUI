#ifndef _JIA_XCHART_
#define _JIA_XCHART_

#include <deque>
#include "XCheck.h"
namespace XE{
class XChart:public XControlBasic
{
private:
	static const int m_chartMaxLineSum = 12;
	static XFColor m_chartLineColor[m_chartMaxLineSum];
	bool m_isInited;
	bool m_withPoint;
	char m_chooseArm;
	bool m_neadUpdateAllLineData;
	bool m_neddUpdateCurLineData;

	XRect m_dataRect;

	int m_horizontalNetSum;
	int m_verticalNetSum;

	std::deque<XVector2> m_datas[m_chartMaxLineSum];
	int m_maxDataSum;

	XCheck m_dataChecks[m_chartMaxLineSum];
	int m_maxLineLen;

	XVector2 m_baseValue;
	XVector2 m_sizeValue;

	XRect m_dataRange;
	int m_dataSum;
	XVector2 m_showDataRange;

	XFontUnicode m_caption;
	XFontUnicode m_textFont;

	XVector2 m_firstNetValue;
	XVector2 m_stepWidth;
	int m_dataAccuracyX;
	int m_dataAccuracyY;

	void checkRange();
	void updateRange();

	unsigned int m_v[m_chartMaxLineSum];
	void allLineUpdateVbo();
	unsigned int m_curPoint[m_chartMaxLineSum];
	unsigned int m_curV[m_chartMaxLineSum];
	void curLineUpdateVbo();
	int m_linePointSum[m_chartMaxLineSum];
	int m_linePointsSum[m_chartMaxLineSum];
	float *m_drawDataBuff;
	int m_drawDataBuffSize;

	static void chartChkCtrlFun(void *,int,int);
	bool checkCanHideLine();

	float m_downHeight;
	float m_allLineRectHeight;
public:
	bool initWithoutSkin(const XRect &rect,const char *caption,const XFontUnicode &font);
	bool initWithoutSkin(const XRect &rect,const char *caption) {return initWithoutSkin(rect,caption,XEE::systemFont);}
	bool initWithoutSkin(const XVector2 &pixelSize,const char *caption)
	{
		return initWithoutSkin(XRect(0.0f,0.0f,pixelSize.x,pixelSize.y),caption,XEE::systemFont);
	}
protected:
	void draw();
	void drawUp();
	void update(int stepTime);
	XBool mouseProc(float x,float y,XMouseState mouseState);
	XBool keyboardProc(int,XKeyState) {return XFalse;}
	void insertChar(const char *,int){;}
	XBool canGetFocus(float x,float y);
	XBool canLostFocus(float,float) {return XTrue;}
public:
	int getMaxDataSum()const{ return m_maxDataSum; }
	void setMaxDataSum(int sum);
	using XObjectBasic::setPosition;
	void setPosition(float x,float y);

	using XObjectBasic::setScale;
	void setScale(float x,float y);
	void insertData(const XVector2 &data,int lineIndex);
	void setLineName(const std::string &name,int lineIndex);

	XBool isInRect(float x,float y);
	XVector2 getBox(int order);
	using XObjectBasic::setColor;
	void setColor(float r,float g,float b,float a);
	void setAlpha(float a);
	void release();
	void setDrawPointer(bool flag);
	bool getDrawPointer(){return m_withPoint;}
	void disable();
	void enable();
	XChart()
		:m_isInited(false)
		,m_baseValue(0.0f,0.0f)
		,m_sizeValue(1.0f,1.0f)

		,m_chooseArm(0)
		,m_dataSum(0)
		,m_maxLineLen(0)
		,m_drawDataBuff(NULL)
		,m_withPoint(false)
		,m_neadUpdateAllLineData(false)
		,m_neddUpdateCurLineData(false)
		, m_maxDataSum(-1)
	{
		m_ctrlType = CTRL_OBJ_CHART;
	}
	~XChart(){release();}

	XBool readDataFromFile(const char * filename);
	XBool saveDataToFile(const char * filename);
};
#if WITH_INLINE_FILE
#include "XChart.inl"
#endif
}
#endif