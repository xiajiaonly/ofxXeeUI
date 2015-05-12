#ifndef XMOVIE_
#define XMOVIE_

#include "XMovieCore.h"
#include "XFfmpeg.h"
#include "XCritical.h"
#include "XSprite.h"

namespace XE{

#define BUFF_TIMER (10.0f)
class XMovieFfmpeg:public XMovieCore
{
private:
	XBool m_isLoaded;
	void release() {}
public:
	XMovieFfmpeg();
	virtual ~XMovieFfmpeg(){closeClip();}

	XBool load(const char *filename,XColorMode mode = COLOR_RGB,bool withVoice = true);

	int getClipWide() const {return m_videoWidth;}
	int getClipHeigh() const {return m_videoHeight;}

	void setLoop(XBool isLoop) {m_isLoop = isLoop;}
	double getCurrentPlayingTime() const
	{
		return m_curFrameNumber*(1000.0/m_curFrameRate);
	}
	int getCurFrameIndex() const {return m_curFrameNumber;}
	int getCurPlayTime() const {return m_curPlayedTime;}
	int getAllFrameSum() const {return m_allFrameSum;}
	int getAllTime(void) const
	{
		return ((double)pFormatCtx->duration * 0.001f);
	}
	float getVideoFrameRate() const {return m_curFrameRate;}
	XBool getUpdateFlag(void)
	{
		if(m_videoQueue.nb_pict > 0) return XTrue;
		else return XFalse;
	}

	XBool getIsEnd() const {return m_isEnd;}
	XBool getIsLoop() const {return m_isLoop;}

	void pause() {if(!m_isEnd) m_isStop = true;}
	void play();
	XBool isPlaying() const {return !m_isStop && !m_isEnd;}
	void closeClip(void);
	void gotoFrame(float temp);
	void gotoFrameIndex(int index);
	void gotoTime(int t);
	void setAutoTime(bool flag) {m_autoTimer = flag;}

private:
	unsigned char *m_curFrameData;

	XVideoFrameData *m_bmp[MAX_BUFF_DEEP];
	AVPicture m_framePic[MAX_BUFF_DEEP];
	int m_curBuffPoint;
	XBool m_needVoice;
	XBool m_autoTimer;

	XTexture *m_movieTex;
	bool m_isGetFirstFrame;
	bool m_isTexInit;
	bool m_isNewFrame;
	XCritical m_mutex;
	XColorMode m_outColorMode;
	XCritical m_gotoMutex;
	XCritical m_gotoMutex1;
public:
	XColorMode getColorMode()const{return m_outColorMode;}
	XSprite *m_movieSprite;
	XBool updateFrame();
	XBool haveNewFrame();
	void pixelLock() {m_mutex.Lock();}
	unsigned char * getDataP() {return m_curFrameData;}
	void pixelUnlock() {m_mutex.Unlock();}
	void getData(unsigned char * p);
	void updateTex(XTexture &tex);
	void draw();
	unsigned int * getTexture() {return (unsigned int *)&m_movieTex->m_texture;}
private:

	SwsContext *m_pSwsContext;
	int imgConvert(AVPicture *dst,const AVPicture *src,int src_height);

	SwrContext *m_pSwrContext;
private:
	XVideoQueue m_videoQueue;
	XAudioQueue m_audioQueue;
	AVFormatContext *pFormatCtx;
	AVCodecContext *pCodeCtx;
	AVCodecContext *aCodeCtx;
	int m_sreAudioFmt;
	AVFrame *pFrame;
	AVFrame *pAudioFrame;
	AVPacket packet;
	int videoStream;
	int audioStream;

	XBool m_isBuffing;

	XBool m_isStop;
	XBool m_isEnd;
	XBool m_isQuit;
	unsigned long m_curPlayedTime;
	XBool m_isDecodeOver;

	unsigned long m_allFrameSum;
	unsigned long m_curFrameNumber;
	float m_curFrameRate;
	int m_videoWidth;
	int m_videoHeight;
	XBool m_isLoop;

	std::string videofilename;
	XBool m_isThreadDecoderExit;
	XBool m_isThreadDrawExit;

	void getPixelData();
	XBool getFirstPixelData();
#ifdef XEE_OS_LINUX
	static void *decoderThread(void *arg);
	static void *drawThread(void *arg);
	static void audioCallBack(void *userdata,Uint8 *stream,int len);
#endif
#ifdef XEE_OS_WINDOWS
	static DWORD WINAPI decoderThread(void *arg);
	static DWORD WINAPI drawThread(void *arg);
	static void audioCallBack(void *userdata,Uint8 *stream,int len);
#endif
	void initAudioQueue();
	void initVideoPictList();
	void releaseAudioQueue();
	void releaseVideoPictList();
	int putIntoPacketQueue();
	int getFromPacketQueue(AVPacket *pkt);
	int audioDecodeFrame(uint8_t *audio_buf,int buf_size);
	void putIntoVideoPicList();
	unsigned char * getFormVideoPicList();
	unsigned char * getAVideoFrame();
	void clearAudioQueue();
	void clearVideoQueue();

	uint8_t m_audioBuf[(AVCODEC_MAX_AUDIO_FRAME_SIZE * 3) / 2];
	unsigned int m_audioBufSize;
	unsigned int m_audioBufIndex;

public:
	void replay();
	bool withVideo()const{return videoStream >= 0;}
	bool withAudio()const{return audioStream >= 0;}
};
#if WITH_INLINE_FILE
#include "XMovieFfmpeg.inl"
#endif
}
#endif
