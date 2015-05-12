#ifndef _JIA_XAUDIOSTREAM_
#define _JIA_XAUDIOSTREAM_

#include "XBasicWindow.h"
#include "XBasicFun.h"
#include "XFfmpeg.h"
namespace XE{
class XAudioStream
{
private:
	XBool m_isLoaded;
	AVFormatContext *m_pFormatCtx;
	AVCodecContext *m_pAudioCodecCtx;
	AVFrame *m_pFrame;
	AVPacket m_dataPacket;
	int m_allFrameSum;

	SwrContext *m_pSwrContext;
	uint8_t m_audioBuf[(AVCODEC_MAX_AUDIO_FRAME_SIZE * 3) / 2];
	int m_dataLen;
public:
	unsigned char * getData() {return m_audioBuf;}
	int getDataLen() const {return m_dataLen;}
	XBool load(const char * filename);
	XBool getAFrame();
	void close()
	{
		if(!m_isLoaded) return;
		av_frame_free(&m_pFrame);
		av_free_packet(&m_dataPacket);
		avcodec_close(m_pAudioCodecCtx);
		avformat_close_input(&m_pFormatCtx);
		swr_free(&m_pSwrContext);
		m_isLoaded = XFalse;
	}
	void gotoFrame(float temp)
	{
		if(temp < 0.0f) temp = 0.0f;
		if(temp > 1.0f) temp = 1.0f;

		av_seek_frame(m_pFormatCtx,0,temp * m_allFrameSum,AVSEEK_FLAG_BACKWARD);
	}
	XAudioStream()
		:m_isLoaded(XFalse)
		,m_pFormatCtx(NULL)
		,m_pAudioCodecCtx(NULL)
		,m_pFrame(NULL)
		,m_pSwrContext(NULL)
	{}
	~XAudioStream() {close();}
};
}
#endif