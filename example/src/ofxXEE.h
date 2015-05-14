#ifndef _JIA_UI_
#define _JIA_UI_
#include "ofMain.h"
#include "XEffeEngine.h"
#undef main
class ofxXEE:public XE::XGameBasic,public ofBaseApp
{
private:
	bool XSetup();
	bool XUpdate();
	bool XDraw();
	bool XKeyDown(int key);
	bool XKeyUp(int key);
	bool XMouseMoved(int x,int y,int button);
	bool XMouseDragged(int x,int y,int button);
	bool XMousePressed(int x,int y,int button);
	bool XMouseReleased(int x,int y,int button);
public:
	virtual void setup(ofEventArgs & args){
		XSetup();
		setup();
	}
	virtual void update(ofEventArgs & args){
		XUpdate();
		update();
	}
	virtual void draw(ofEventArgs & args){
		draw();
		XDraw();
	}
	virtual void keyPressed( ofKeyEventArgs & key ){
		XKeyDown(key.key);
		keyPressed(key.key);
	}
	virtual void keyReleased( ofKeyEventArgs & key ){
		XKeyUp(key.key);
		keyReleased(key.key);
	}

	virtual void mouseMoved( ofMouseEventArgs & mouse ){
		mouseX=mouse.x;
		mouseY=mouse.y;
		XMouseMoved(mouse.x,mouse.y,mouse.button);
		mouseMoved(mouse.x,mouse.y);
	}
	virtual void mouseDragged( ofMouseEventArgs & mouse ){
		mouseX=mouse.x;
		mouseY=mouse.y;
		XMouseDragged(mouse.x,mouse.y,mouse.button);
		mouseDragged(mouse.x,mouse.y,mouse.button);
	}
	virtual void mousePressed( ofMouseEventArgs & mouse ){
		mouseX=mouse.x;
		mouseY=mouse.y;
		XMousePressed(mouse.x,mouse.y,mouse.button);
		mousePressed(mouse.x,mouse.y,mouse.button);
	}
	virtual void mouseReleased(ofMouseEventArgs & mouse){
		mouseX=mouse.x;
		mouseY=mouse.y;
		XMouseReleased(mouse.x,mouse.y,mouse.button);
		mouseReleased(mouse.x,mouse.y,mouse.button);
	}

	bool init(){return true;}
	void move(int){}
	//void draw(){}
	void input(const XE::XInputEvent &){}
	void release(){}

	virtual void setup(){}
	virtual void update(){}
	virtual void draw(){}

	virtual void keyPressed( int key ){}
	virtual void keyReleased( int key ){}

	virtual void mouseMoved( int x, int y ){}
	virtual void mouseDragged( int x, int y, int button ){}
	virtual void mousePressed( int x, int y, int button ){}
	virtual void mouseReleased(int x, int y, int button ){}
};
#endif