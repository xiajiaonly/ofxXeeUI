#ifndef _JIA_MOVIECORE_
#define _JIA_MOVIECORE_

#include "XOSDefine.h"
#include "XCommonDefine.h"
namespace XE{

class XTexture;
class XMovieCore
{
protected:
public:
	virtual ~XMovieCore() {}
	virtual XBool load(const char *filename,XColorMode mode = COLOR_RGB,bool withVoice = true) = 0;
	virtual XBool updateFrame() = 0;
	virtual void draw() = 0;
	virtual void updateTex(XTexture &tex) = 0;
	virtual unsigned int * getTexture() = 0;

	virtual void pause() = 0;
	virtual void play() = 0;
	virtual XBool isPlaying()const = 0;
	virtual void closeClip(void) = 0;
	virtual void setLoop(XBool isLoop) = 0;
	virtual XBool getIsLoop()const = 0;
	virtual XBool getIsEnd()const = 0;
	virtual double getCurrentPlayingTime() const = 0;
};
template<typename T>
class XMovie
{
private:
	XMovieCore *m_pObj;
public:
	XMovie(){m_pObj = XMem::createMem<T>();}
	~XMovie(){XMem::XDELETE(m_pObj);}
	XBool load(const char *filename) {return m_pObj->load(filename);}
	XBool updateFrame() {return m_pObj->updateFrame();}
	void draw() {m_pObj->draw();}
	void updateTex(XTexture &tex) {m_pObj->updateTex(tex);}
	unsigned int * getTexture() {return m_pObj->getTexture();}

	virtual void pause(){m_pObj->pause();}
	virtual void play(){m_pObj->play();}
	virtual XBool isPlaying(){return m_pObj->isPlaying();}
	void closeClip(void) {m_pObj->closeClip();}
	void setLoop(XBool isLoop) {m_pObj->setLoop(isLoop);}
	XBool getIsLoop() {return m_pObj->getIsLoop(isLoop);}
	XBool getIsEnd() {return m_pObj->getIsEnd(isLoop);};
	double getCurrentPlayingTime() const {return m_pObj->getCurrentPlayingTime();};
};
}
#endif