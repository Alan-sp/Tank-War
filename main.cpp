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
#include "main_game.h"
#include "MyThread.h"
#include "wall.cpp"



int arg0 = 1;
int& arg1 = arg0;
char **arg2;

resource_lib statics::resource_library;
QApplication statics::qapp(arg1,arg2);
TankWarGUI statics::gui;

int main()
{
	statics st;
	st.gui.show();

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