#include "ofApp.h"
void ofApp::ctrlEventProc(int id,int eventID)
{
	if(id == btn.getControlID() && eventID == XE::XButton::BTN_MOUSE_DOWN)
	{
		printf("Btn press down!\n");
	}
}
void ofApp::setup(){
	//init UI items
	tmp.initWithoutSkin(256,"ÄãºÃ");
	tmp.setPosition(200,10);
	cmb.initWithoutSkin(256,5,3);
	cmb.setPosition(200,100);
	btn.initWithoutSkin("hello",128);
	btn.setPosition(200,200);

	img.loadImage("../../../OscTool.png");
}
void ofApp::update(){
}
void ofApp::draw(){
	ofSetColor(255,255,255,255);
	img.draw(0,0);
}
void ofApp::keyPressed(int key){
}
void ofApp::keyReleased(int key){
}
void ofApp::mouseMoved(int x, int y){
}
void ofApp::mouseDragged(int x, int y, int button){
}
void ofApp::mousePressed(int x, int y, int button){
}
void ofApp::mouseReleased(int x, int y, int button){
}
void ofApp::windowResized(int w, int h){
}
void ofApp::gotMessage(ofMessage msg){
}
void ofApp::dragEvent(ofDragInfo dragInfo){
}