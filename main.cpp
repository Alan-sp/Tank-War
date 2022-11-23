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
    
    //wall w(0, 0, 0); tank t(4, 4, 3.1415926 / 3);
    //double tx[4] = { 2,2,-2,-2 }, ty[4] = { 2,-2,-2,2 };//4*4square
    //plane_model wm(4); plane_model tm(4, tx, ty);
    //st.resource_library.add_model_resource(1, wm);
    //st.resource_library.add_model_resource(2, tm);
    //collapse_result cr = t.collapseWith(w);
    //printf("%s:%lf,%lf",cr.isCollapse?"Yes":"No",cr.dx,cr.dy);

    /*st.resource_library.add_image_resource(2, "D:/q.jpg");

    QThread thd;
    MyThread mthd;
    mthd.moveToThread(&thd);
    thd.start();

    QObject::connect(&st.gui, SIGNAL(repaint_signal()), &st.gui, SLOT(repaint_slot()));
    QObject::connect(&mthd, SIGNAL(MyThreadTTRan()), &mthd, SLOT(ran()));

    emit mthd.MyThreadTTRan();

    st.qapp.exec();

    main_game* new_game = new main_game;
    while (new_game->game_mode) {
	    new_game->flushed(new_game);
    }*/

    return 0;
}