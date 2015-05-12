#ifndef _JIA_XSOUND_
#define _JIA_XSOUND_

#include "XSoundCommon.h"
#include "XBasicFun.h"
#include "XResourceManager.h"

#include <vector>
namespace XE{

#define MIN_SOUND_DELAY (50)

struct XSoundInfo
{
	void * sound;
	XResourceInfo *resInfo;
	int soundTime;

	XBool isSlowDownInit;
	XBool isEnableSlowDown;
	unsigned char *slowDownOldData;
	int slowDownOldLen;
	unsigned char *slowDownNewData;
	int slowDownNewLen;
	int slowDownRate;
	int lateChannel;

	XSoundInfo()
		:sound(NULL)
		,resInfo(NULL)
		,isSlowDownInit(XFalse)
		,isEnableSlowDown()
		,slowDownOldData(NULL)
		,slowDownNewData(NULL)
		,soundTime(-1)
		,lateChannel(-1)
	{}
};

typedef int XSndHandle;

class XSound
{

protected:
	XSound();
	XSound(const XSound&);
	XSound &operator= (const XSound&);
	virtual ~XSound();
public:
	static XSound& GetInstance()
	{
		static XSound m_instance;
		return m_instance;
	}

private:
	XResourcePosition m_resoursePosition;
private:
	std::vector<XSoundInfo *> m_sound;

	int m_soundVolume;
	XBool m_firstAddSoundFlag;
public:
	XSndHandle addSound(const char* filename,XResourcePosition resoursePosition = RESOURCE_SYSTEM_DEFINE);
	void clearUp();
	void clearOneSound(XSndHandle soundHandle);
	XBool play(XSndHandle soundHandle,int loops = 0);
	void setSoundVolume(int volume);
	void setAllVolume(int volume);

	XBool slowDownInit(int rate,XSndHandle handle);
	void enableSlowDown(XSndHandle handle);
	void disableSlowDown(XSndHandle handle);
	void slowDownRelease(XSndHandle handle);
	XBool slowDownAllInit(int rate);
	void enableAllSlowDown();
	void disableAllSlowDown();
	void slowDownAllRelease();

	void pause(XSndHandle s)
	{
		if(s < 0 || s >= m_sound.size() || m_sound[s] == NULL) return;
		XSoundHandle.pauseSound(m_sound[s]->lateChannel);
	}
	void resume(XSndHandle s)
	{
		if(s < 0 || s >= m_sound.size() || m_sound[s] == NULL) return;
		XSoundHandle.resumeSound(m_sound[s]->lateChannel);
	}
	XBool isPause(XSndHandle s)
	{
		if(s < 0 || s >= m_sound.size() || m_sound[s] == NULL) return XFalse;
		return XSoundHandle.isSoundPause(m_sound[s]->lateChannel);
	}
	void stop(XSndHandle s)
	{
		if(s < 0 || s >= m_sound.size() || m_sound[s] == NULL) return;
		XSoundHandle.soundFadeOut(m_sound[s]->lateChannel,100);
	}
	XBool isEnd(XSndHandle s)
	{
		if(s < 0 || s >= m_sound.size() || m_sound[s] == NULL) return XTrue;
		return !XSoundHandle.isSoundPlaying(m_sound[s]->lateChannel);
	}
	XBool fadeInSound(XSndHandle s,int loops,int ms);
	void fadeOutSound(XSndHandle s,int ms)
	{
		if(s < 0 || s >= m_sound.size() || m_sound[s] == NULL) return;
		XSoundHandle.soundFadeOut(m_sound[s]->lateChannel,ms);
	}
	void release()
	{
		XSoundHandle.haltSound();
		clearUp();
	}
};
inline void XSound::setSoundVolume(int volume)
{
	if(volume < 0) volume = 0;
	if(volume > 128) volume = 128;
	m_soundVolume = volume;
}
inline void XSound::setAllVolume(int volume)
{
	if(volume < 0) volume = 0;
	if(volume > 128) volume = 128;
	m_soundVolume = volume;
	XSoundHandle.setVolume(-1,m_soundVolume);
}
}
#endif