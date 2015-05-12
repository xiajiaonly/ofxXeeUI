#ifndef _JIA_XFFMPEGEX_
#define _JIA_XFFMPEGEX_

#include "XMovieCore.h"
#include "XFfmpeg.h"
#include "XCritical.h"
#include "XThread.h"
#include "XSprite.h"
namespace XE{

enum XPlayerState
{
	PSTATE_END,
	PSTATE_PLAYING,
	PSTATE_PAUSE,
};

class XFfmpegEx
{
protected:
	XPlayerState m_playerState;
	bool m_isLoad;

	bool m_isDecodeOver;
	bool m_isVideoOver;
	bool m_isAudioOver;
	bool m_isAudioDecodeOver;
	bool m_haveNewFrame;

	bool m_withVideo;
	bool m_withAudio;
	bool m_needAudio;

	int m_videoWidth;
	int m_videoHeight;
	int m_videoDataSize;

	int m_loopTimes;
	double m_allTime;
	double m_currentTimer;
	unsigned long m_curVideoFrameIndex;
	unsigned long m_curAudioFrameIndex;

	unsigned long m_allVideoFrameSum;
	unsigned long m_allAudioFrameSum;
	float m_videoFps;
	float m_audioFps;
	float m_oneVideoFrameTime;
	float m_oneAudioFrameTime;

	std::string m_filename;

	XVideoQueue m_videoQueue;
	XAudioQueueEx m_audioQueue;
	void pushAVideoPkt2Queue(bool isEnd = false);
	unsigned char *popAVideoFrameFromQueue(bool flag = true);
	void pushAAudioPkt2Queue(bool isEnd = false);
	XAudioFrameData *popAAudioPktFromQueue();
	void decodeAudioPkt();
	void decodeAAudioPkt(AVPacket pkt);
	void initAudioQueue();
	void initVideoQueue();
	void releaseAudioQueue();
	void releaseVideoQueue();

	void clearVideoQueue();
	void clearAudioQueue();

	AVFormatContext *m_pFormatCtx;
	AVCodecContext *m_pVideoCodeCtx;
	AVCodecContext *m_pAudioCodeCtx;
	AVFrame *m_pVideoFrame;
	AVFrame *m_pAudioFrame;
	AVPacket m_dataPacket;

	XVideoFrameData *m_bmp[MAX_BUFF_DEEP];
	AVPicture m_framePic[MAX_BUFF_DEEP];
	int m_curBuffIndex;

	int m_sreAudioFmt;
	SwrContext *m_pSwrContext;
	XBool createAudioConverter();
	void releaseAudioConverter();
	SwsContext *m_pSwsContext;
	XBool createVideoConverter();
	void releaseVideoConverter();
	XColorMode m_outColorMode;

	unsigned char *m_curVideoPixels;
	int imgConvert(AVPicture *dst,const AVPicture *src);

	int m_videoStreamIndex;
	int m_audioStreamIndex;

	unsigned char *m_audioBuf;
	unsigned long m_audioBufSize;
	unsigned long m_audioBufIndex;
	unsigned long m_maxAudioBufSize;

	XCritical m_mutex;

	float m_playSpeed;
public:
	float getPlaySpeed()const{return m_playSpeed;}
	void setPlaySpeed(float s){if(s <= 0.0f) return;m_playSpeed = s;}
public:
	XFfmpegEx()
		:m_isLoad(false)

		,m_videoWidth(0)
		,m_videoHeight(0)
		,m_withVideo(false)
		,m_withAudio(false)
		,m_loopTimes(0)
		,m_allTime(0.0)
		,m_allVideoFrameSum(0)
		,m_allAudioFrameSum(0)
		,m_videoFps(30.0f)
		,m_audioFps(30.0f)
		,m_oneVideoFrameTime(33.3333333f)
		,m_oneAudioFrameTime(33.3333333f)
		,m_filename("")
		,m_pFormatCtx(NULL)
		,m_pVideoCodeCtx(NULL)
		,m_pAudioCodeCtx(NULL)
		,m_pVideoFrame(NULL)
		,m_pAudioFrame(NULL)
		,m_videoStreamIndex(-1)
		,m_audioStreamIndex(-1)
		,m_needAudio(true)
		,m_sreAudioFmt(AUDIO_S16)
		,m_pSwrContext(NULL)
		,m_pSwsContext(NULL)
		,m_outColorMode(COLOR_RGB)
		,m_curVideoPixels(NULL)
		,m_isDecodeOver(false)
		,m_isVideoOver(false)
		,m_isAudioOver(false)
		,m_isAudioDecodeOver(false)
		,m_currentTimer(0.0)
		,m_curVideoFrameIndex(0)
		,m_curAudioFrameIndex(0)
		,m_haveNewFrame(false)
		,m_playerState(PSTATE_END)
		,m_audioBuf(NULL)
		,m_audioBufSize(0)
		,m_audioBufIndex(0)
		,m_maxAudioBufSize(0)
		,m_needJumpTo(false)
		,m_jumpRate(0)
		,m_playSpeed(1.0f)
	{}
	virtual ~XFfmpegEx(){release();}

	virtual XBool load(const char * filename,XColorMode mode = COLOR_RGB,bool withVoice = true);
	virtual void release();
	bool getIsLoaded() const {return m_isLoad;}

	void play(int loopTimes = 0,float rate = 0.0f);
	void stop();
	void pause()
	{
		if(m_playerState != PSTATE_PLAYING) return;
		m_playerState = PSTATE_PAUSE;
	}
	void resume()
	{
		if(m_playerState == PSTATE_PAUSE)
			m_playerState = PSTATE_PLAYING;
	}

private:
	void setLoop(int times){m_loopTimes = times;}
public:
	XBool getIsLoop() const {return m_loopTimes == 0;}

	bool getIsPlayEnd() const {return m_playerState == PSTATE_END;}
	bool getIsPlaying() const {return m_playerState == PSTATE_PLAYING;}

	double getAllTime()const{return m_allTime;}
	double getCurrentTime()const
	{
		if(m_needJumpTo) return m_jumpRate * m_allTime;
		return m_currentTimer;
	}
private:
	bool gotoRate(float rate);
	bool m_needJumpTo;
	float m_jumpRate;
	XCritical m_jumpMutex;
	void jumpProc();
	void jumpAudioStream(XPlayerState tmpState);
public:
	bool getWithVideo() const {return m_withVideo;}
	bool getWithAudio() const {return m_withAudio;}

	int getVideoWidth() const {return m_videoWidth;}
	int getVideoHeight() const {return m_videoHeight;}

	void pixelLock() {m_mutex.Lock();}
	void pixelUnlock() {m_mutex.Unlock();}
	unsigned char* getVideoPixelData()const {return m_curVideoPixels;}
	XColorMode getColorMode()const {return m_outColorMode;}

	float getFps() const;
	unsigned long getAllFrameSum() const;
	unsigned long getCurrentFrame()const
	{
		if(m_withVideo) return m_curVideoFrameIndex;
		else return m_curAudioFrameIndex;
	}
	bool getHaveNewFrame();
private:

	XThreadState m_decoderThreadState;
	static DWORD WINAPI decoderThreadEx(void *arg);
	XThreadState m_timerThreadState;
	static DWORD WINAPI timerThread(void *arg);
	static void audioCBProc(void *userdata,Uint8 *stream,int len);

	void updateVideoPixel();
protected:

	XBool getFirstVideoFrame();
};
class XFfmpegSpriteEx:public XFfmpegEx,public XMovieCore
{
private:
	XSprite *m_pSprite;
	XTextureData *m_pTextureData;
	XBool m_getFirstVideoFrame;
public:
	virtual XBool load(const char * filename,XColorMode mode = COLOR_RGB,bool withVoice = true);
	virtual void release();
	virtual XBool updateFrame();
	virtual void draw(){if(m_pSprite != NULL) m_pSprite->draw();}
	void setPosition(float x,float y);
	void setPosition(const XVector2 & pos){setPosition(pos.x,pos.y);}
	XVector2 getPosition() const;
	void setScale(float x,float y){if(m_pSprite != NULL) m_pSprite->setScale(x,y);}
	void setScale(float s){setScale(s,s);}
	void setColor(float r,float g,float b,float a = 1.0f);

	virtual void updateTex(XTexture &tex);
	virtual unsigned int * getTexture()
	{
		if(m_pTextureData == NULL) return NULL;
		return &(m_pTextureData->texture.m_texture);
	}

	virtual void pause(){XFfmpegEx::pause();}
	virtual void play() {XFfmpegEx::play();}
	virtual void play(int loopTimes,float rate = 0.0f) {XFfmpegEx::play(loopTimes,rate);}
	virtual XBool isPlaying()const {return getIsPlaying();}
	virtual void closeClip(void) {release();}
	virtual void setLoop(XBool isLoop) {isLoop?m_loopTimes = -1:m_loopTimes = 0;}
	virtual XBool getIsLoop()const {return XFfmpegEx::getIsLoop();}
	virtual XBool getIsEnd()const {return getIsPlayEnd();}
	virtual double getCurrentPlayingTime() const {return getCurrentTime();}

	XFfmpegSpriteEx()
		:m_pSprite(NULL)
		,m_pTextureData(NULL)
		,m_getFirstVideoFrame(false)
	{}
	virtual ~XFfmpegSpriteEx(){release();}
};
#if WITH_INLINE_FILE
#include "XFfmpegEx.inl"
#endif
}
#endif