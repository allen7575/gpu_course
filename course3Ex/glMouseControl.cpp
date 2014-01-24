//#include <stdio.h>
//#include "../window.h"
#include "../camera.h"
#include "../glMouseControl.h"

glMouseControl::glMouseControl(MyInputListener *inputlistener, MyPerspectiveCamera *camera)
{
	mouseListener = inputlistener;
	mousecamera = camera;

	//SetInputListener(mouseListener);
}

void glMouseControl::MouseControlRender()
{
	mousecamera->position += mousecamera->lookat * mouseListener->mouseScroll * 0.1 * (abs(dot(mousecamera->position,mousecamera->lookat))+5);

	if(mouseListener->mouseMiddle){
		mousecamera->position -= mousecamera->right * mouseListener->dx * 0.0025 * (abs(dot(mousecamera->position,mousecamera->lookat))+5) ;
		mousecamera->position += mousecamera->up * mouseListener->dy * 0.0025 * (abs(dot(mousecamera->position,mousecamera->lookat))+5) ;
	}

	if(mouseListener->mouseRight)
	{
		Matrix3x3 head = Matrix3x3::RotateAxis(mousecamera->up, -mouseListener->dx * 0.00002*(abs(dot(mousecamera->position,mousecamera->lookat))+50) );
		mousecamera->lookat = head * mousecamera->lookat;
		mousecamera->right = head *  mousecamera->right;

		Matrix3x3 pitch = Matrix3x3::RotateAxis(mousecamera->right, -mouseListener->dy * 0.00002*(abs(dot(mousecamera->position,mousecamera->lookat))+50) );
		mousecamera->lookat = pitch * mousecamera->lookat;
		mousecamera->up = pitch *  mousecamera->up;

		//make sure right is horizontal
		mousecamera->right.z = 0;
		mousecamera->right.Normalize();
		mousecamera->lookat = cross(mousecamera->up, mousecamera->right);
		mousecamera->up = cross(mousecamera->right, mousecamera->lookat);
	}

	mouseListener->ClearState();
}