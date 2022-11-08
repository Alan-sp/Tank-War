#pragma once
#include "ImageResource.h"
#include "TankWarGUI.h"
//static variables
/*usage:
* statics st;
* st.image_resourse.xxxx
*/

class statics {
public:

	static QApplication qapp;
	static ImageResource image_resourse;
	static TankWarGUI gui;
};