#pragma once
#include<iostream>
#include<bitset>
#include <QtConcurrent>
#include <qthread.h>
#include <QtWidgets/QApplication>
#include <string>

#include "statics.h"
int arg0 = 1;
int& arg1 = arg0;
char** arg2;
QApplication statics::qapp(arg1, arg2);
#include "resource_lib.h"
#include "TankWarGUI.h"
#include "main_game.h"
#include "MyThread.h"
TankWarGUI* statics::gamegui = new TankWarGUI();
resource_lib* statics::resource_library = new resource_lib();
main_game* statics::maingame = new main_game();
MyThread* statics::mthd = new MyThread();

#include "object.h"
#include "bullet.cpp"
#include "tank.cpp"
#include "rolling_wall.h"
#include "wall.cpp"
#include "base64.cpp"

int main()
{
	statics st;
	srand(time(NULL));

	double tx[4] = { 32,32,-50,-50 }, ty[4] = { 32,-32,-32,32 };//Tank
	double wx[4] = { 5,5,-5,-5 }, wy[4] = { 100,-100,-100,100 };
	double bx[4] = { 20,20,-20,-20 }, by[4] = { 20,-20,-20,20 };
	double shortwallx[4] = { 5,5,-5,-5 }, shortwally[4] = { 25,-25,-25,25 };
	double midwallx[4] = { 5,5,-5,-5 }, midwally[4] = { 50,-50,-50,50 };
	double blockx[4] = { 50,50,-50,-50 }, blocky[4] = { 50,-50,-50,50 };
	plane_model wm(4, wx, wy); plane_model tm(4, tx, ty);
	plane_model bm(5.0); plane_model fm(4,bx,by);
	plane_model swm(4, shortwallx, shortwally); plane_model mwm(4, midwallx, midwally);
	plane_model blockm(4, blockx, blocky);
	st.resource_library->add_model_resource(1, wm);
	st.resource_library->add_model_resource(3, bm);
	st.resource_library->add_model_resource(21, tm);
	st.resource_library->add_model_resource(22, tm);
	st.resource_library->add_model_resource(23, tm);
	st.resource_library->add_model_resource(10, swm);
	st.resource_library->add_model_resource(11, mwm);
	st.resource_library->add_model_resource(12, blockm);
	st.resource_library->add_image_resource(1, "./Resforgame/w.jpg");
	st.resource_library->add_image_resource(21, "./Resforgame/tank1.png");
	st.resource_library->add_image_resource(22, "./Resforgame/tank2.png");
	st.resource_library->add_image_resource(23, "./Resforgame/tank3.png");
	st.resource_library->add_image_resource(3, "./Resforgame/b.png");
	st.resource_library->add_image_resource(10, "./Resforgame/sw.jpg");
	st.resource_library->add_image_resource(11, "./Resforgame/mw.jpg");
	st.resource_library->add_image_resource(12, "./Resforgame/block.jpg");
	for (int i = 1; i <=4 ; i++) {
		char str[2010];
		snprintf(str, 2000, "./Resforgame/buff/buff%d.png", i);
		st.resource_library->add_image_resource(50 + i, str);
		st.resource_library->add_model_resource(50 + i, fm);
	}
	for(int i=1;i<20;i++){
		char str[2010];
		snprintf(str, 2000, "./Resforgame/boom/bang%d.png", i);
		st.resource_library->add_image_resource(100 + i, str);
	}

	QThread thd;
	//mthd.ran();
	st.mthd->moveToThread(&thd);
	thd.start();
	QObject::connect(st.gamegui, SIGNAL(repaint_signal()), st.gamegui, SLOT(repaint_slot()));
	QObject::connect(st.mthd, SIGNAL(MyThreadTTRan()), st.mthd, SLOT(ran()));
	QObject::connect(st.mthd, SIGNAL(MyThreadTTEnd()), st.mthd, SLOT(stoq()));

	//emit mthd.MyThreadTTRan();

	st.gamegui->show();
	st.qapp.exec();

	return 0;
}