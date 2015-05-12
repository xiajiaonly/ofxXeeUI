#ifndef _JIA_XMUSIC_
#define _JIA_XMUSIC_

#include "XSoundCommon.h"
#include "XLogBook.h"
#include <vector>
namespace XE{

typedef int XMusicHandle;
class XMusic
{

protected:
	XMusic()
		:m_firstAddMusicFlag(XFalse)
	{
		m_music.clear();
	}
	XMusic(const XMusic&);
	XMusic &operator= (const XMusic&);
	virtual ~XMusic()
	{
		XSoundHandle.haltMusic();
		clearUp();
	}
public:
	static XMusic& GetInstance()
	{
		static XMusic m_instance;
		return m_instance;
	}

private:
	std::vector<void *> m_music;

	int m_musicVolume;
	XBool m_firstAddMusicFlag;
public:
	XMusicHandle addMusic(const char *fileName);
	void clearUp();
	void clearOneMusic(XMusicHandle musicHandle);
	XBool playMusic(XMusicHandle musicHandle,int loop = 0);
	void setMusicVolume(int volume);
	void fadeOutMusic(int ms);
	XBool fadeInMusic(XMusicHandle musicHandle,int loop = 0,int ms = 0);

	XBool isEnd() {return !XSoundHandle.isMusicPlaying();}
	void pause(){XSoundHandle.pauseMusic();}
	void resume(){XSoundHandle.resumeMusic();}
	void rewind(){XSoundHandle.rewindMusic();}
	XBool isPause() {return XSoundHandle.isMusicPause();}
};
inline XBool XMusic::fadeInMusic(XMusicHandle musicHandle,int loop,int ms)
{
	if(musicHandle < 0 || musicHandle >= m_music.size()
		|| m_music[musicHandle] == NULL) return XFalse;
	if(XSoundHandle.musicFadeIn(m_music[musicHandle],loop,ms) == -1) return XFalse;
	return XTrue;
}
inline void XMusic::fadeOutMusic(int ms)
{
	XSoundHandle.musicFadeOut(ms);
}
inline void XMusic::clearOneMusic(XMusicHandle musicHandle)
{
	if(musicHandle < 0 || musicHandle >= m_music.size()
		|| m_music[musicHandle] == NULL) return;
	if(m_music[musicHandle] != NULL)
	{
		XSoundHandle.clearMusic(m_music[musicHandle]);
		m_music[musicHandle] = NULL;
	}
}
inline XBool XMusic::playMusic(XMusicHandle musicHandle,int loop)
{
	if(musicHandle < 0 || musicHandle >= m_music.size()
		|| m_music[musicHandle] == NULL) return XFalse;
	if(XSoundHandle.playMusic(m_music[musicHandle],loop) == -1)
	{
		LogStr("Sound play error!");
		return XFalse;
	}
	return XTrue;
}
inline void XMusic::setMusicVolume(int volume)
{
	if(volume < 0) volume = 0;
	if(volume > 128) volume = 128;
	m_musicVolume = volume;
	XSoundHandle.setMusicVolume(m_musicVolume);
}
}
#endif