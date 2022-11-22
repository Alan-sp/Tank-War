#pragma once
#include<iostream>
#include<bitset>
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
    
    double pi = 3.1415926;
    wall obj1(5, 0, pi/4); bullet obj2(0,0,0,0);
    for (int i = 0; i < 10; i++){
	    obj2.ticking();
	    printf("%.2f %.2f\n", obj2.get_x(),obj2.get_y());
    }
    collapse_result res{};
    obj2.collapse(&obj1, res);
    printf("-------%.2fPi-------\n",obj2.get_direction());
    for (int i = 0; i < 10; i++) {
	    obj2.ticking();
	    printf("%.2f %.2f\n", obj2.get_x(), obj2.get_y());
    }

    /*st.resource_library.add_image_resource(2, "D:/q.jpg");

    QThread thd;
    MyThread mthd;
    mthd.moveToThread(&thd);
    thd.start();

    QObject::connect(&st.gui, SIGNAL(repaint_signal()), &st.gui, SLOT(repaint_slot()));
    QObject::connect(&mthd, SIGNAL(MyThreadTTRan()), &mthd, SLOT(ran()));

    emit mthd.MyThreadTTRan();*/

    //st.qapp.exec();

    main_game* new_game = new main_game;
    /*while (new_game->game_mode) {
	    new_game->flushed(new_game);
    }*/

    return 0;
}