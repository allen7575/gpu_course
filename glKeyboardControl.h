#ifndef GL_KEYBOARD_CONTROL
#define GL_KEYBOARD_CONTROL

#include "MyInputListener.h"
#include "glCube.h"

class glKeyboardControl
{
public:
	explicit glKeyboardControl(MyInputListener *inputlistener, glCube *cube);
	void KeyboardControlRender();

private:
	MyInputListener *keyboardListener;
	glCube *cubeptr;

};

#endif