#pragma once
#include<iostream>
#include<bitset>
#include <QtConcurrent>
#include <qthread.h>
#include <QtWidgets/QApplication>

#include "statics.h"
#include "object.h"
#include "bullet.cpp"
#include "tank.cpp"
#include "rolling_wall.h"
#include "main_game.h"
#include "MyThread.h"
#include "wall.cpp"



int arg0 = 1;
int& arg1 = arg0;
char **arg2;

resource_lib statics::resource_library=resource_lib();
QApplication statics::qapp(arg1,arg2);
TankWarGUI statics::gui;
main_game statics::maingame;

int main()
{
	statics st;
	st.gui.show();

	st.maingame.obj_pool.push_back(new wall(5, 100, 0));
	st.maingame.obj_pool.push_back(new wall(1195, 100, 0));
	st.maingame.obj_pool.push_back(new wall(5, 300, 0));
	st.maingame.obj_pool.push_back(new wall(1195, 300, 0));
	st.maingame.obj_pool.push_back(new wall(5, 500, 0));
	st.maingame.obj_pool.push_back(new wall(1195, 500, 0));
	st.maingame.obj_pool.push_back(new wall(5, 700, 0));
	st.maingame.obj_pool.push_back(new wall(1195, 700, 0));
	st.maingame.obj_pool.push_back(new wall(100, 5, 3.1415926 / 2));
	st.maingame.obj_pool.push_back(new wall(100, 795, 3.1415926 / 2));
	st.maingame.obj_pool.push_back(new wall(300, 5, 3.1415926 / 2));
	st.maingame.obj_pool.push_back(new wall(300, 795, 3.1415926 / 2));
	st.maingame.obj_pool.push_back(new wall(500, 5, 3.1415926 / 2));
	st.maingame.obj_pool.push_back(new wall(500, 795, 3.1415926 / 2));
	st.maingame.obj_pool.push_back(new wall(700, 5, 3.1415926 / 2));
	st.maingame.obj_pool.push_back(new wall(700, 795, 3.1415926 / 2));
	st.maingame.obj_pool.push_back(new wall(900, 5, 3.1415926 / 2));
	st.maingame.obj_pool.push_back(new wall(900, 795, 3.1415926 / 2));
	st.maingame.obj_pool.push_back(new wall(1100, 5, 3.1415926 / 2));
	st.maingame.obj_pool.push_back(new wall(1100, 795, 3.1415926 / 2));

	st.maingame.obj_pool.push_back(new rolling_wall(200, 200, 1, 0.05));
	st.maingame.obj_pool.push_back(new wall(500, 500, 3));
	st.maingame.obj_pool.push_back(new rolling_wall(200, 500, 9, -0.03));
	st.maingame.obj_pool.push_back(new wall(700, 700, 5));
	st.maingame.obj_pool.push_back(new rolling_wall(1000, 200, 10, 0.01));

	for(int i=0;i<10;i++)
	st.maingame.obj_pool.push_back(new bullet(500, 500, i, 1));

	st.maingame.obj_pool.push_back(new tank(100, 100, 0, 1, 87, 65, 83, 68, 32));
	st.maingame.obj_pool.push_back(new tank(500, 200, 0, 2, 38, 37, 40, 39, 163));

	double tx[4] = { 32,32,-50,-50 }, ty[4] = { 32,-32,-32,32 };//Tank
	double wx[4] = { 5,5,-5,-5 }, wy[4] = { 100,-100,-100,100 };
	plane_model wm(4, wx, wy); plane_model tm(4, tx, ty); plane_model bm(5.0);
	st.resource_library.add_model_resource(1, wm);
	st.resource_library.add_model_resource(3, bm);
	st.resource_library.add_model_resource(21, tm);
	st.resource_library.add_model_resource(22, tm);
	st.resource_library.add_model_resource(23, tm);
	st.resource_library.add_image_resource(1, "D:/Resforgame/w.jpg");
	st.resource_library.add_image_resource(21, "D:/Resforgame/tank1.png");
	st.resource_library.add_image_resource(22, "D:/Resforgame/tank2.png");
	st.resource_library.add_image_resource(23, "D:/Resforgame/tank3.png");
	st.resource_library.add_image_resource(3, "D:/Resforgame/b.jpg");

	QThread thd;
	MyThread mthd;
	//mthd.ran();
	mthd.moveToThread(&thd);
	thd.start();
	QObject::connect(&st.gui, SIGNAL(repaint_signal()), &st.gui, SLOT(repaint_slot()));
	QObject::connect(&mthd, SIGNAL(MyThreadTTRan()), &mthd, SLOT(ran()));
	emit mthd.MyThreadTTRan();

	st.qapp.exec();

	return 0;
}