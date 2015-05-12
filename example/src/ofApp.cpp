#include "ofApp.h"
#include "ofxXEEInterface.h"
#include "UI.h"
void ofApp::UIEvent(int id,int eventID,void*pClass)
{
	ofApp &app = *(ofApp *)pClass;
	if(id == UIMain.btn.getControlID() && eventID == XE::XButton::BTN_MOUSE_DOWN)
	{
		printf("°´Å¥°´ÏÂ!\n");
	}
}
void ofApp::setup(){
	XSetup(UIEvent,this);
}

void ofApp::update(){
	XUpdate();
}

void ofApp::draw(){
	XDraw();
}
void ofApp::keyPressed(int key){
	XKeyDown(key);
}

void ofApp::keyReleased(int key){
	XKeyUp(key);
}

void ofApp::mouseMoved(int x, int y){
	XMouseMoved(x,y,0);
}

void ofApp::mouseDragged(int x, int y, int button){
	XMouseDragged(x,y,button);
}

void ofApp::mousePressed(int x, int y, int button){
	XMousePressed(x,y,button);
}

void ofApp::mouseReleased(int x, int y, int button){
	XMouseReleased(x,y,button);
}

void ofApp::windowResized(int w, int h){

}

void ofApp::gotMessage(ofMessage msg){

}

void ofApp::dragEvent(ofDragInfo dragInfo){

}