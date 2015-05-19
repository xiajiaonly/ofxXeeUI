#pragma once
#include "ofMain.h"
#include "ofxXEE.h"
class ofApp : public ofxXEE{
	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
		void ctrlEventProc(int id,int eventID);
		//TODO:Define UI items
		XE::XEdit tmp;
		XE::XCombo cmb;
		XE::XButton btn;

		ofImage img;
};
