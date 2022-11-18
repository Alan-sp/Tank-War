#pragma once
#include<iostream>
#include<bitset>
#include <qthread.h>
#include <QtWidgets/QApplication>

#include "object.h"
#include "bullet.cpp"
#include "tank.cpp"
#include "main_game.h"
#include "MyThread.h"



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
    
    st.resource_library.add_image_resource(2, "D:/q.jpg");

    QThread thd;
    MyThread mthd;
    mthd.moveToThread(&thd);
    thd.start();

    QObject::connect(&st.gui, SIGNAL(repaint_signal()), &st.gui, SLOT(repaint_slot()));
    QObject::connect(&mthd, SIGNAL(MyThreadTTRan()), &mthd, SLOT(ran()));

    emit mthd.MyThreadTTRan();

    st.qapp.exec();

    main_game* new_game = new main_game;
    /*while (new_game->game_mode) {
	    new_game->flushed(new_game);
    }*/

    return 0;
}