#ifndef GL_MOUSE_CONTROL_H
#define GL_MOUSE_CONTROL_H

#include "MyInputListener.h"

class glMouseControl
{
	public:
		explicit glMouseControl(MyInputListener *inputlistener, MyPerspectiveCamera *camera);
		void MouseControlRender();
	private:
		MyInputListener *mouseListener;
		MyPerspectiveCamera *mousecamera;

};


#endif
