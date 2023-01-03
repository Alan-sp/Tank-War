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

int main()
{
	statics st;
	srand(time(NULL));

	std::string code1("11 1 500 500 3 1 841 561 3.8 2 200 200 1 0.05 2 658 349 -1 -0.03 2 1000 200 10 0.01 1 167 552 0 1 261 453 4.7 1 365 549 0 1 268 647 -1.6 4 500 200 0 4 269 551 0");
	st.maingame->load_map(code1);

	double tx[4] = { 32,32,-50,-50 }, ty[4] = { 32,-32,-32,32 };//Tank
	double wx[4] = { 5,5,-5,-5 }, wy[4] = { 100,-100,-100,100 };
	double bx[4] = { 20,20,-20,-20 }, by[4] = { 20,-20,-20,20 };
	plane_model wm(4, wx, wy); plane_model tm(4, tx, ty);
	plane_model bm(5.0); plane_model fm(4,bx,by);
	st.resource_library->add_model_resource(1, wm);
	st.resource_library->add_model_resource(3, bm);
	st.resource_library->add_model_resource(21, tm);
	st.resource_library->add_model_resource(22, tm);
	st.resource_library->add_model_resource(23, tm);
	st.resource_library->add_image_resource(1, "D:/Resforgame/w.jpg");
	st.resource_library->add_image_resource(21, "D:/Resforgame/tank1.png");
	st.resource_library->add_image_resource(22, "D:/Resforgame/tank2.png");
	st.resource_library->add_image_resource(23, "D:/Resforgame/tank3.png");
	st.resource_library->add_image_resource(3, "D:/Resforgame/b.jpg");
	for (int i = 1; i <=4 ; i++) {
		char str[2010];
		snprintf(str, 2000, "D:/Resforgame/buff/buff%d.png", i);
		st.resource_library->add_image_resource(50 + i, str);
		st.resource_library->add_model_resource(50 + i, fm);
	}
	for(int i=1;i<20;i++){
		char str[2010];
		snprintf(str, 2000, "D:/Resforgame/boom/bang%d.png", i);
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