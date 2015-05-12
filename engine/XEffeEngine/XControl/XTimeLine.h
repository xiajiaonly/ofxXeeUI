#ifndef _JIA_XTIMELINE_
#define _JIA_XTIMELINE_
#include "../XXml.h"
#include "../XFont/XNumberEx.h"
#include "../XMath/XVector2.h"
#include "../XMath/XMoveData.h"
#include "../XFont/XFontUnicode.h"
#include "XText.h"
#include "XEdit.h"
#include "XSlider.h"
namespace XE{
#define TIMELINE_HEIGHT (32.0f)
#define TIMELINE_SLD_WIDTH (32.0f)
#define TIMELINE_TITLE_LEN (128.0f)
#define TIMELINE_FRAME_WIDTH (10.0f)
#define DEFAULT_TIMELINE_NAME ("timeLine.xml")

enum XFrameType
{
	FRAME_TYPE_KEY,
	FRAME_TYPE_INTER,
	FRAME_TYPE_BLANK,
	FRAME_TYPE_LAST,
};

class XFrameDataBasic
{
protected:
	int type;
public:
	void * pData;
	XFrameDataBasic()
		:pData(NULL)
		,type(0)
	{}
	virtual ~XFrameDataBasic(){XMem::XDELETE(pData);}

	virtual XBool writeToXml(TiXmlElement * node) = 0;
	virtual XBool readFromXml(TiXmlNode * node) = 0;
};
extern XFrameDataBasic * createFrameDataBasic(TiXmlNode * node);
struct XOneFrame
{
	int frameIndex;
	int time;
	int timeLen;
	XMoveDataMode interpolationMode;
	XFrameDataBasic *pData;
	bool overFlag;
	XOneFrame()
		:time(0)
		,interpolationMode(MOVE_DATA_MODE_LINE)
		,pData(NULL)
		,overFlag(false)
		,timeLen(0)
	{}
};
class XOneTimeLine
{
public:
	XFontUnicode m_title;
	XVector2 m_position;
	XVector2 m_scale;
	int m_startIndex;
	int m_width;
	float m_frameTimeWidth;

	XBool m_isInited;
public:
	void setPosition(float x,float y)
	{
		m_position.set(x,y);
		m_title.setPosition(m_position);
	}
	void setScale(float x,float y)
	{
		m_scale.set(x,y);
		m_title.setScale(x,y);
	}
	void setCurStartIndex(int index){m_startIndex = index;}
	std::string m_name;
	std::vector<XOneFrame> m_keyFrames;
	XFrameType getFrameType(int index);
	void setFps(int fps)
	{
		m_frameTimeWidth = 1000.0f / fps;
		for(unsigned int i = 0;i < m_keyFrames.size();++ i)
		{
			m_keyFrames[i].frameIndex = (int)(m_keyFrames[i].time / m_frameTimeWidth);
		}
	}

	XBool init(const std::string &name,int width,const XVector2 &position,const XVector2 &scale);
	void draw();
	XOneTimeLine()
		:m_isInited(XFalse)
		,m_frameTimeWidth(33.33f)
		,m_width(256)
		,m_startIndex(0)
	{}
	void addAKeyFrame(int time,int timeLen,XFrameDataBasic * data,XMoveDataMode mode = MOVE_DATA_MODE_NULL);
	void delAKeyFrame(int time);
	void moveKeyFrame(int fromTime,int toTime);
	void clearAllFrame()
	{
		for(unsigned int  i = 0;i < m_keyFrames.size();++ i)
		{
			XMem::XDELETE(m_keyFrames[i].pData);
		}
		m_keyFrames.clear();
	}
	~XOneTimeLine(){clearAllFrame();}

	const XOneFrame *getCurKeyFrame(float time)
	{
		for(unsigned int  i = 0;i < m_keyFrames.size();++ i)
		{
			if(m_keyFrames[i].time == (int)time) return &m_keyFrames[i];
			if(m_keyFrames[i].time > time)
			{
				if(i > 0) return &m_keyFrames[i - 1];
				else return NULL;
			}
		}
		if(m_keyFrames.size() > 0) return &m_keyFrames[(int)(m_keyFrames.size()) - 1];
		else return NULL;
	}
	const XOneFrame *getNextKeyFrame(float time)
	{
		for(unsigned int  i = 0;i < m_keyFrames.size();++ i)
		{
			if(m_keyFrames[i].time > time) return &m_keyFrames[i];
		}
		return NULL;
	}
	void resetAllFrameFlag()
	{
		for(unsigned int  i = 0;i < m_keyFrames.size();++ i)
		{
			m_keyFrames[i].overFlag = false;
		}
	}
	void setAllFrameFlag()
	{
		for(unsigned int  i = 0;i < m_keyFrames.size();++ i)
		{
			m_keyFrames[i].overFlag = true;
		}
	}
	void resetAllFrameFlag(int from,int to);
	void setAllFrameFlag(int from,int to);
	void resetAllFrameFlagBefore(int time);
	void setAllFrameFlagBefore(int time);
	void resetAllFrameFlagAfter(int time);
	void setAllFrameFlagAfter(int time);
};
class XTimeLines
{
private:
	int m_objectID;

	XVector2 m_position;
	XVector2 m_scale;
	float m_width;

	std::vector<XOneTimeLine *> m_timeLines;

	XText m_curTimeTxt;
	XText m_fpsTxt;
	XEdit m_fpsEdt;
	XText m_allTimeTxt;
	XEdit m_allTimeEdt;
	XButton m_playOrStopBtn;
	XButton m_headBtn;
	XButton m_endBtn;
	XSlider m_timeSld;
	XSlider m_timeLineSld;
	int m_showTimeLineSum;
	int m_curStartTimeLineIndex;

	int m_curStartIndex;
	int m_canShowFrameSum;

	int m_fps;
	float m_frameTime;
	int m_allTime;
	int m_curTimer;
	int m_curChooseIndex;

	XBool m_isInited;
	XBool m_visible;
	bool m_isPlaying;
	bool m_needShowRuleHead;
	bool m_needShowRuleMiddle;
	bool m_needShowRuleEnd;

	bool m_isMouseDrag;
	bool m_isMouseMove;
	int m_mouseDragTLIndex;
	int m_mouseDragKFTime;

	float m_canShowTime;

	XFontUnicode m_ruleHead;
	float m_ruleHeadOffset;
	XFontUnicode m_ruleMiddle;
	float m_ruleMiddleOffset;
	XFontUnicode m_ruleEnd;
	float m_ruleEndOffset;

	static void ctrlProc(void*,int,int);
public:
	int getCurChooseIndex() const {return m_curChooseIndex;}
	void play();
	void stop();
	bool getIsPlaying() const {return m_isPlaying;}
	void setCurTimer(int curTime) {m_curTimer = curTime;}
private:
	void updateCtrlsPosition();
	void updateRule();

	void (*m_funTimeChange)(void *,int ID);
	void (*m_funPlay)(void *,int ID);
	void (*m_funStop)(void *,int ID);
	void *m_pClass;
public:
	void setTimeChangeCB(void (* funTimeChange)(void *,int),
		void (* funPlay)(void *,int),
		void (* funStop)(void *,int),
		void *pClass = NULL)
	{
		m_funTimeChange = funTimeChange;
		m_funPlay = funPlay;
		m_funStop = funStop;
		m_pClass = pClass;
	}
	void setPosition(float x,float y);
	void setSize(float x,float y);
	void setCurTimeSlider(float p);
	void setCurTimeLineSlider(float p);
	void setToPrev();
	void setToNext();

	XBool addATimeLine(const std::string &name);

	XBool addKeyFrame(const std::string &name,int time,int timeLen,XFrameDataBasic * data,XMoveDataMode mode = MOVE_DATA_MODE_NULL);

	XBool addKeyFrame(unsigned int index,int time,int timeLen,XFrameDataBasic * data,XMoveDataMode mode = MOVE_DATA_MODE_NULL);
	XBool delCurKeyFrame(const std::string &name);
	XBool delCurKeyFrame(unsigned int index);
	XBool clearAllFroms(const std::string &name);
	XBool clearAllFroms(unsigned int index);
	void clearAllFroms();

	XBool mouseProc(float x,float y,XMouseState mouseState);
	int getTimeLineIndexByName(const std::string &name);
	void setFps(int fps);
	int getFps() const {return m_fps;}
	void setAllTime(int time);
	int getAllTime() const {return m_allTime;}
	XBool init(float width,int showLineSum,int fps = 30);
	void draw();
	void move(int stepTime);
	void release();
	XTimeLines()
		:m_isInited(XFalse)
		,m_fps(30)
		,m_curStartIndex(0)
		,m_allTime(6000)
		,m_curTimer(0)
		,m_isPlaying(false)
		,m_curChooseIndex(-1)
		,m_showTimeLineSum(3)
		,m_curStartTimeLineIndex(0)
		,m_needShowRuleHead(false)
		,m_needShowRuleMiddle(false)
		,m_needShowRuleEnd(false)
		,m_ruleHeadOffset(0.0f)
		,m_ruleMiddleOffset(0.0f)
		,m_ruleEndOffset(0.0f)
		,m_funTimeChange(NULL)
		,m_pClass(NULL)
		,m_objectID(100)
		,m_isMouseDrag(false)
		,m_visible(true)
	{}
	~XTimeLines(){release();}
	int getControlID() const{return m_objectID;}

	XBool saveToFile(const char * filename = NULL);
	XBool readFromFile(const char * filename = NULL);
	int getCurTimer() const {return m_curTimer;}

	const XOneFrame *getCurKeyFrame(const std::string &name);
	const XOneFrame *getNextKeyFrame(const std::string &name);
	const XOneFrame *getCurKeyFrame(unsigned int index);
	const XOneFrame *getNextKeyFrame(unsigned int index);
	void resetAllTimeLineFrameFlag();
	void setAllTimeLineFrameFlag();
	void resetAllTimeLineFrameFlag(int index);
	void resetAllTimeLineFrameFlag(const std::string &name);
	void setAllTimeLineFrameFlag(int index);
	void setAllTimeLineFrameFlag(const std::string &name);

	void setVisible()
	{
		m_visible = XTrue;
		m_curTimeTxt.setVisible();
		m_fpsTxt.setVisible();
		m_fpsEdt.setVisible();
		m_allTimeTxt.setVisible();
		m_allTimeEdt.setVisible();
		m_playOrStopBtn.setVisible();
		m_headBtn.setVisible();
		m_endBtn.setVisible();
		m_timeSld.setVisible();
		m_timeLineSld.setVisible();
	}
	void disVisible()
	{
		m_visible = XFalse;
		m_curTimeTxt.disVisible();
		m_fpsTxt.disVisible();
		m_fpsEdt.disVisible();
		m_allTimeTxt.disVisible();
		m_allTimeEdt.disVisible();
		m_playOrStopBtn.disVisible();
		m_headBtn.disVisible();
		m_endBtn.disVisible();
		m_timeSld.disVisible();
		m_timeLineSld.disVisible();
	}
	XBool getVisible() const {return m_visible;}
};
#if WITH_INLINE_FILE
#include "XTimeLine.inl"
#endif
}
#endif