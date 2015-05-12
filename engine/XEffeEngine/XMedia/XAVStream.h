#ifndef _JIA_XAVSTREAM_
#define _JIA_XAVSTREAM_

#include "XFfmpeg.h"
#include "XBasicFun.h"
#include "XBasicClass.h"
#include "XMicrophone.h"
#include "XAudioStream.h"

#include <stdio.h>
namespace XE{
struct XAudioInfo
{
	int channelSum;
	AVSampleFormat sampleFormat;
	int sampleRate;
};
enum XAudioDeviceType
{
	AUDIO_DEVICE_TYPE_MIC,
	AUDIO_DEVICE_TYPE_FILE,
};
enum XAVStreamQuality
{
	AVS_QUALITY_HEIGHT,
	AVS_QUALITY_MIDDLE,
	AVS_QUALITY_LOW,
};

class XAVStream
{
private:
	XBool m_isOpen;

	int m_videoWidth;
	int m_videoHight;
	int m_videoFrameRate;
	AVStream * m_videoST;
    AVStream * m_audioST;
	AVFormatContext *m_pOutContext;
	AVOutputFormat *m_pFormat;

	AVFrame * m_pictureYUV;
	AVFrame * m_pictureRGB;

	int m_audioOutbufSize;
	uint8_t *m_audioOutbuf;
	uint8_t *m_audioTempBuff;
	int m_audioDataPos;
	int m_audioFrameSize;
	int m_audioFrameInSize;

	XBool m_audioBuffFlag;

	AVFrame *m_audioFrame;
	SwrContext *m_audioSwr;
	AVPacket m_audioPkt;

	int m_videoOutbufSize;
	uint8_t *m_videoOutbuf;
	AVPacket m_videoPkt;

	AVStream *openAudio();
	void closeAudio()
	{
		avcodec_close(m_audioST->codec);

		XMem::XDELETE_ARRAY(m_audioOutbuf);
		XMem::XDELETE_ARRAY(m_audioTempBuff);
	}

	AVStream *openVideo(XAVStreamQuality quality = AVS_QUALITY_HEIGHT);
	void closeVideo()
	{
		avcodec_close(m_videoST->codec);

		XMem::XDELETE_ARRAY(m_videoOutbuf);
	}

	float m_autoTimer;
	float m_frameTime;

	SwsContext *m_pSwsContext;
	int imgConvert(AVPicture *dst,const AVPicture *src,int src_height)
	{
		if(m_pSwsContext == NULL) return 0;
		return sws_scale(m_pSwsContext, src->data, src->linesize,
            0,src_height, dst->data, dst->linesize);
	}
	XBool audioNeedData() const
	{
		int len = 0;
		switch(m_audioInfo.sampleFormat)
		{
		case AV_SAMPLE_FMT_U8:len = 1;break;
		case AV_SAMPLE_FMT_S16:len = 2;break;
		case AV_SAMPLE_FMT_S32:len = 4;break;
		case AV_SAMPLE_FMT_FLT:len = 4;break;
		case AV_SAMPLE_FMT_U8P:len = 1;break;
		case AV_SAMPLE_FMT_S16P:len = 2;break;
		case AV_SAMPLE_FMT_S32P:len = 4;break;
		case AV_SAMPLE_FMT_FLTP:len = 4;break;
		}
		return m_videoFrameIndex * m_audioInfo.sampleRate * m_audioInfo.channelSum * len / m_videoFrameRate > m_inputAudioDataSum;
	}
	XBool openFile(const char *filename,int width,int height,int frameRate,
		XAudioInfo *info = NULL,XAVStreamQuality quality = AVS_QUALITY_HEIGHT);
	void pushVideoFrame();

	void flushAudioQueue();
	void flushVideoQueue();
	XAudioInfo m_audioInfo;

	int m_inputAudioDataSum;
private:
	int m_videoFrameIndex;

public:

	XBool open(const char *filename,int width,int height,int frameRate,
		XAudioInfo *info = NULL,XAVStreamQuality quality = AVS_QUALITY_HEIGHT);
	void addFrameAudio(const unsigned char * data,int size);
	void addFrameRGB(unsigned char*p);

	void addFrameAudio(XMicrophone & mic)
	{
		int ret = 0;
		unsigned char * audioData = mic.getCaptureData(&ret);
		if(ret != 0 && audioNeedData())  addFrameAudio(audioData,ret * mic.getByteRate());
	}
	void addFrameAudio(XAudioStream & aStr)
	{
		while(audioNeedData())
		{
			if(aStr.getAFrame()) addFrameAudio(aStr.getData(),aStr.getDataLen());
			Sleep(1);
		}
	}

	XBool open(const char *filename,int width,int height,int frameRate,void * audioDevice,
		XAudioDeviceType deviceType = AUDIO_DEVICE_TYPE_MIC,XAudioInfo *info = NULL,
		XAVStreamQuality quality = AVS_QUALITY_HEIGHT);
	void updataFrameRGB(unsigned char*p){addFrameRGB(p);}
	void setStop()
	{
		if(m_audioDeviceType == AUDIO_DEVICE_TYPE_MIC)
			((XMicrophone *)m_audioDevice)->captureStop();
		m_isStop = XTrue;
	}
	void setStart()
	{
		if(m_audioDeviceType == AUDIO_DEVICE_TYPE_MIC)
			((XMicrophone *)m_audioDevice)->captureStart();
		m_isStop = XFalse;
	}
private:
	XCritical m_mutex;
	void * m_audioDevice;
	XAudioDeviceType m_audioDeviceType;
	XBool m_isStop;
	XBool m_withThread;
	XThreadState m_threadState;
	pthread_t m_encodeThread;
	static DWORD WINAPI encodeThread(void * pParam);
public:

	XBool openEx(const char *filename,int width,int height,int frameRate,const char * deviceName = NULL,
		XAudioDeviceType deviceType = AUDIO_DEVICE_TYPE_MIC);
private:
	XBool m_withDevice;
	XMicrophone m_micDevice;
	XAudioStream m_AudioStream;
public:

	XBool close();
	float getFrameTime() const {return m_frameTime;}

	XAVStream()
		:m_isOpen(XFalse)
		,m_videoWidth(0)
		,m_videoHight(0)
		,m_videoFrameRate(30)
		,m_videoST(NULL)
		,m_audioST(NULL)
		,m_pOutContext(NULL)
		,m_pFormat(NULL)
		,m_pictureYUV(NULL)
		,m_pictureRGB(NULL)

		,m_audioOutbufSize(0)
		,m_audioOutbuf(NULL)
		,m_audioTempBuff(NULL)

		,m_videoOutbufSize(0)
		,m_videoOutbuf(NULL)
		,m_audioFrame(NULL)
		,m_audioSwr(NULL)
	{}
};
}
#endif