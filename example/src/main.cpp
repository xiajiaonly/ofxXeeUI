#include "ofMain.h"
#include "ofApp.h"
//Environment="PATH=%PATH%;.\..\engine\dll\libfreetype;.\..\engine\dll\SDL;.\..\engine\dll\gl;.\..\engine\dll\MemoryPool;.\..\addons\XOpenCV\dll;.\..\addons\XKinectMS\dll;.\..\engine\dll\ffmpeg;"	//��Ҫ����dll·��
//========================================================================
int main(){
	ofSetupOpenGL(1024,768,OF_WINDOW);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new ofApp());
}
