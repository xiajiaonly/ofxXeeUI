#ifndef _JIA_XFFMPEG_
#define _JIA_XFFMPEG_

#include "XOSDefine.h"

#ifdef XEE_OS_WINDOWS
#include <Windows.h>
extern "C"
{
#include "libavformat/avformat.h"
#include "libavcodec/avcodec.h"
#include "libswscale/swscale.h"
#include "libswresample/swresample.h"
#include "libavutil/opt.h"
#include "libavutil/imgutils.h"
}
#endif
#ifdef XEE_OS_LINUX
#include <pthread.h>
#include "avformat.h"
#include "avcodec.h"
#endif

#pragma comment(lib, "../../engine/lib/ffmpeg/avcodec.lib")
#pragma comment(lib, "../../engine/lib/ffmpeg/avformat.lib")
#pragma comment(lib, "../../engine/lib/ffmpeg/avutil.lib")
#pragma comment(lib, "../../engine/lib/ffmpeg/swresample.lib")
#pragma comment(lib, "../../engine/lib/ffmpeg/swscale.lib")

#include "SDL.h"

namespace XE{
#ifndef AVCODEC_MAX_AUDIO_FRAME_SIZE
#define AVCODEC_MAX_AUDIO_FRAME_SIZE (192000)
#endif

struct XVideoFrameData
{
	AVPicture *pict;
	unsigned char *data;
	XVideoFrameData *next;
	bool isOverFrame;
	XVideoFrameData()
		:pict(NULL)
		,data(NULL)
		,next(NULL)
		,isOverFrame(false)
	{}
};

struct XVideoQueue
{
	XVideoFrameData *first_pict;
	XVideoFrameData *last_pict;
	int nb_pict;
	SDL_mutex *mutex;
	XVideoQueue()
		:first_pict(NULL)
		,last_pict(NULL)
		,mutex(NULL)
		,nb_pict(0)
	{}
};

struct XAudioFrameData
{
    AVPacket pkt;
    XAudioFrameData *next;
	bool isOverFrame;
	XAudioFrameData()
		:next(NULL)
		,isOverFrame(false)
	{}
};

struct XAudioQueueEx
{
	XAudioFrameData *first_pkt;
	XAudioFrameData *last_pkt;
	int nb_packets;
	int size;
	SDL_mutex *mutex;

	XAudioQueueEx()
		:first_pkt(NULL)
		,last_pkt(NULL)
		,mutex(NULL)

		,nb_packets(0)
		,size(0)
	{}
};

struct XAudioQueue
{
	AVPacketList *first_pkt;
	AVPacketList *last_pkt;
	int nb_packets;
	int size;
	SDL_mutex *mutex;
	SDL_cond *cond;
	XAudioQueue()
		:first_pkt(NULL)
		,last_pkt(NULL)
		,mutex(NULL)
		,cond(NULL)
		,nb_packets(0)
		,size(0)
	{}
};
#define MAX_BUFF_DEEP (6)

namespace XFfmpeg
{
	inline int img_convert(AVPicture *dst, AVPixelFormat dst_pix_fmt,
					const AVPicture *src, AVPixelFormat src_pix_fmt,
					int src_width, int src_height)
	{
		SwsContext *pSwsCtx = sws_getContext(src_width,src_height,src_pix_fmt,
								src_width,src_height,dst_pix_fmt,
								SWS_BICUBIC,NULL,NULL,NULL);
		sws_scale(pSwsCtx, src->data, src->linesize,
				0,src_height, dst->data, dst->linesize);
		sws_freeContext(pSwsCtx);
		return 0;
	}
}
}
#endif