
//#include "../window.h"
#include "../glKeyboardControl.h"

glKeyboardControl::glKeyboardControl(MyInputListener *inputlistener, glCube *cube)
{
	keyboardListener = inputlistener;
	//SetInputListener(keyboardListener);
	cubeptr = cube;
}

void glKeyboardControl::KeyboardControlRender()
{
	//cubeptr->Translation(Vector3(0,1,0));
	if(keyboardListener->moveRight){
		cubeptr->Translation(Vector3(0,0.1,0));
	}

	if(keyboardListener->moveLeft){
		cubeptr->Translation(Vector3(0,-0.1,0));
	}

	if(keyboardListener->moveForward){
		cubeptr->Translation(Vector3(-0.1,0,0));
	}

	if(keyboardListener->moveBackward){
		cubeptr->Translation(Vector3(0.1,0,0));
	}

	//keyboardListener->ClearState();

}