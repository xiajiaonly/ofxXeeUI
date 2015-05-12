#pragma once

extern bool XSetup(void (*)(int,int,void*),void *);
extern bool XUpdate();
extern bool XDraw();
extern bool XKeyDown(int key);
extern bool XKeyUp(int key);
extern bool XMouseMoved(int x,int y,int button);
extern bool XMouseDragged(int x,int y,int button);
extern bool XMousePressed(int x,int y,int button);
extern bool XMouseReleased(int x,int y,int button);