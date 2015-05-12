#ifndef _JIA_XVIDEOSTREAM_
#define _JIA_XVIDEOSTREAM_

#include "XFfmpeg.h"
namespace XE{
#define VEDIO_STREAM_FORMAT (AV_CODEC_ID_MPEG2VIDEO)

class XVideoEncode
{
private:
	XBool m_isOpen;
	AVCodecContext *m_videoCodec;
	AVFrame *m_pFrameRGB;
	AVFrame *m_pFrameYUV;
	int m_videoOutbufSize;
    uint8_t *m_videoOutbuf;

	SwsContext *m_pSwsContext;
	int imgConvert(AVPicture *dst,const AVPicture *src,int src_height)
	{
		if(m_pSwsContext == NULL) return 0;
		return sws_scale(m_pSwsContext, src->data, src->linesize,
            0,src_height, dst->data, dst->linesize);
	}
public:
	AVPacket m_packet;
	int m_videoFrameIndex;
public:
	XBool open(int w,int h,int rate);
	XBool encodeDataRGB(unsigned char *in);
	void release();

	XVideoEncode()
		:m_isOpen(XFalse)
		,m_videoCodec(NULL)
		,m_pFrameRGB(NULL)
		,m_pFrameYUV(NULL)
		,m_videoOutbuf(NULL)
	{}
	~XVideoEncode(){release();}
};

class XVideoDecode
{
private:
	XBool m_isOpen;
	AVCodecContext *m_videoCodec;

	AVFrame *m_pFrame;
	AVPacket m_packet;
	unsigned char *m_pixelData;
	AVPicture m_frameData;

	SwsContext *m_pSwsContext;
	int imgConvert(AVPicture *dst,const AVPicture *src,int src_height)
	{
		return sws_scale(m_pSwsContext, src->data, src->linesize,
            0,src_height, dst->data, dst->linesize);
	}
public:
	XBool open(int w,int h);
	XBool decodeData(void * data,int len);
	void release();
	unsigned char *getPixels() {return m_pixelData;}

	XVideoDecode()
		:m_isOpen(XFalse)
		,m_pFrame(NULL)
		,m_pixelData(NULL)
		,m_videoCodec(NULL)
		,m_pSwsContext(NULL)
	{}
	~XVideoDecode(){release();}
};
}
#endif