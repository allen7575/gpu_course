
#include "../MyInputListener.h"


MyInputListener::MyInputListener()
{
	ClearState();
	mouseRight = false;
	mouseMiddle = false;
	mouseLeft = false;

	moveForward = false;
	moveBackward = false;
	moveRight = false;
	moveLeft = false;

	shoot = false;
}


void MyInputListener::OnMouseMove(const int x, const int y, const int deltaX, const int deltaY)
{
		dx = deltaX;
		dy = deltaY;
}

void MyInputListener::OnMouseButton(const int x, const int y, const MouseButton button, const bool pressed)
	{
		switch(button){
		case MOUSE_RIGHT:
			mouseRight = pressed;
			break;
		case MOUSE_MIDDLE:
			mouseMiddle = pressed;
			break;
		case MOUSE_LEFT:
			mouseLeft = pressed;
			break;
		}

	}
void MyInputListener::OnMouseWheel(const int x, const int y, const int scroll)
{
	mouseScroll = scroll;
}

void MyInputListener::OnKey(const unsigned int key, const bool pressed)
{
	switch(key){
		case KEY_UP:
		case KEY_W:
			moveForward = pressed;
			break;
		case KEY_DOWN:
		case KEY_S:
			moveBackward = pressed;
			break;
		case KEY_RIGHT:
		case KEY_D:
			moveRight = pressed;
			break;
		case KEY_LEFT:
		case KEY_A:
			moveLeft = pressed;
			break;
		case KEY_Z:
			shoot = pressed;
			break;
	}
}

void MyInputListener::ClearState()
{
		dx = 0;
		dy = 0;
		mouseScroll = 0;
}

