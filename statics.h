
#include <QApplication>

#ifndef STATICS_H
#define STATICS_H
//static variables
/*usage:
* statics st;
* st.image_resourse.xxxx
*/

class resource_lib;
class TankWarGUI;
class main_game;
class MyThread;
class MapEditor;

class statics {
public:

	static QApplication qapp;
	static resource_lib* resource_library;
	static TankWarGUI* gamegui;
	static main_game* maingame;
	static MyThread* mthd;
	static MapEditor* mapedit;
};
#endif // !STATICS_H
