#ifndef MY_INPUT_LISTENER
#define MY_INPUT_LISTENER

#include "window.h"

class MyInputListener : public InputListener
{
	friend class glMouseControl;
	friend class glKeyboardControl;

public:
	explicit MyInputListener();

private:
	virtual void OnMouseMove(const int x, const int y, const int deltaX, const int deltaY);

	virtual void OnMouseButton(const int x, const int y, const MouseButton button, const bool pressed);

	virtual void OnMouseWheel(const int x, const int y, const int scroll);

	virtual void OnKey(const unsigned int key, const bool pressed);

	void ClearState();

	bool mouseRight;
	bool mouseMiddle;
	bool mouseLeft;

	bool moveRight;
	bool moveLeft;
	bool moveForward;
	bool moveBackward;

	bool shoot;

	int mouseScroll;
	float dx;
	float dy;

};

#endif