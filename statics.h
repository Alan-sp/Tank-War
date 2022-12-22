#pragma once
#include "resource_lib.h"
#include "TankWarGUI.h"
#include "main_game.h"
#include "MyThread.h"
//static variables
/*usage:
* statics st;
* st.image_resourse.xxxx
*/

class statics {
public:

	static QApplication qapp;
	static resource_lib resource_library;
	static TankWarGUI gui;
	static main_game maingame;
	static MyThread mthd;
};