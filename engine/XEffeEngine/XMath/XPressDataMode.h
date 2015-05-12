#ifndef _JIA_PRESSDATAMODE_
#define _JIA_PRESSDATAMODE_

#include "XOSDefine.h"
#include "XInputEventCore.h"
namespace XE{
enum XPressState
{

	PRESS_STATE_PRESS,
	PRESS_STATE_NORMAL,
};
class XPressDataSingle
{
private:
	float m_maxDeformData;
	float m_normalData;
	float m_curDeformData;
	float m_curData;
	XPressState m_pressState;

	int m_sensitivity;
	int m_curPressTimer;

	float m_startChangeData;
	float m_minChangeData;
	float m_maxChangeData;

	float m_dataFlag;
public:
	XPressDataSingle()
		:m_startChangeData(1.0f)
		,m_minChangeData(0.01f)
		,m_maxChangeData(0.1f)
	{}

	void init(float normalValue,float maxDeformValue,int sensitivity);
	void setParam(float startChange,float minChange,float maxChange)
	{
		m_startChangeData = startChange;
		m_minChangeData = minChange;
		m_maxChangeData = maxChange;
	}
	void setPress();
	void setRelease(){m_pressState = PRESS_STATE_NORMAL;}
	void move(int stepTime);
	float getCurData() const {return m_curData;}
	XBool isPress() const {return m_pressState != PRESS_STATE_NORMAL;}

	void setCurData(float data)
	{
		if(m_normalData > m_maxDeformData)
		{
			if(data < m_maxDeformData) data = m_maxDeformData;
			if(data > m_normalData) data = m_normalData;
		}else
		{
			if(data > m_maxDeformData) data = m_maxDeformData;
			if(data < m_normalData) data = m_normalData;
		}
		m_curData = data;
	}
};

enum XPressDataRecoverMode
{
	MODE_NO_RECOVER,
	MODE_SLOW_RECOVER,
	MODE_IMM_RECOVER,
};
class XPressDataDouble
{
private:
	float m_minDeformData;
	float m_maxDeformData;
	float m_normalData;
	float m_curDeformData;
	float m_curData;
	XPressState m_pressMinState;
	XPressState m_pressMaxState;

	XPressDataRecoverMode m_recoverMode;
	int m_sensitivity;
	int m_curPressTimer;

	float m_startChangeData;
	float m_minChangeData;
	float m_maxChangeData;
	XBool m_isRecover;

	XKeyValue m_minKey;
	XKeyValue m_maxKey;
public:

	void init(float normalValue,float maxDeformValue,float minDeformValue,
		int sensitivity,XPressDataRecoverMode recoverMode = MODE_SLOW_RECOVER);
	void setParam(float startChange,float minChange,float maxChange)
	{
		m_startChangeData = startChange;
		m_minChangeData = minChange;
		m_maxChangeData = maxChange;
	}
	void move(int stepTime);
	float getCurData() const {return m_curData;}
	XBool isPress() const {return (m_pressMinState != PRESS_STATE_NORMAL ||
		m_pressMaxState != PRESS_STATE_NORMAL);}

	void setCurData(float data)
	{
		if(data < m_minDeformData) data = m_minDeformData;
		if(data > m_maxDeformData) data = m_maxDeformData;
		m_curData = data;
		m_isRecover = XFalse;
	}
	XPressDataDouble()
		:m_startChangeData(1.0f)
		,m_minChangeData(0.01f)
		,m_maxChangeData(0.1f)
		,m_minKey(XKEY_LEFT)
		,m_maxKey(XKEY_RIGHT)
	{}

	void setPressMax();
	void setPressMin();
	void setReleaseMin(){m_pressMinState = PRESS_STATE_NORMAL;}
	void setReleaseMax(){m_pressMaxState = PRESS_STATE_NORMAL;}

	void setKeyValue(XKeyValue min,XKeyValue max)
	{
		m_minKey = min;
		m_maxKey = max;
	}
	void updateState(const XInputEvent &e)
	{
		if(e.type != EVENT_KEYBOARD) return;
		if(e.keyState == KEY_STATE_DOWN)
		{
			if(e.keyValue == m_minKey) setPressMin(); else
			if(e.keyValue == m_maxKey) setPressMax();
		}else
		if(e.keyState == KEY_STATE_UP)
		{
			if(e.keyValue == m_minKey) setReleaseMin(); else
			if(e.keyValue == m_maxKey) setReleaseMax();
		}
	}
};
class XKeyPressModel
{
private:
	bool m_isInited;
	bool m_isPress;
	bool m_isKeyDown;
	int m_sensitivity;
	int m_pressSpeed;
	XKeyValue m_keyValue;
	int m_timer;
public:
	XKeyPressModel()
		:m_isInited(false)
		,m_sensitivity(500)
		,m_pressSpeed(100)
		,m_keyValue(XKEY_LEFT)
	{}
	bool init(XKeyValue key,int sensitivity = 500,int pressSpeed = 100)
	{
		m_keyValue = key;
		m_sensitivity = sensitivity;
		m_pressSpeed = pressSpeed;

		m_isPress = false;
		m_isKeyDown = false;
		m_timer = 0;
		m_isInited = true;
		return true;
	}
	bool move(int stepTime)
	{
		if(!m_isInited) return false;
		if(m_isKeyDown)
		{
			m_timer += stepTime;
			if(m_timer >= m_sensitivity)
			{
				m_isPress = true;
				m_timer -= m_pressSpeed;
			}
		}
		if(m_isPress)
		{
			m_isPress = false;
			return true;
		}
		return false;
	}
	void updateState(const XInputEvent &e)
	{
		if(!m_isInited) return;
		if(e.type == EVENT_KEYBOARD && e.keyValue == m_keyValue)
		{
			if(e.keyState == KEY_STATE_DOWN)
			{
				m_isPress = true;
				m_isKeyDown = true;
				m_timer = 0;
			}else
			if(e.keyState == KEY_STATE_UP)
			{
				m_isPress = false;
				m_isKeyDown = false;
			}
		}
	}
};
}
#endif