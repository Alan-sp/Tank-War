#pragma once
#include<iostream>
#include<bitset>
#include<windows.h>
#include "qthread.h"
#include <QtWidgets/QApplication>

#include "bullet.cpp"
#include "object.cpp"
#include "tank.cpp"
#include "TankWarGUI.h"
#include "statics.h"
#include "main_game.h"
#include "ImageResource.h"
#include "MyThread.h"



int arg0 = 1;
int& arg1 = arg0;
char **arg2;

image_resource statics::image_resourse;
QApplication statics::qapp(arg1,arg2);
TankWarGUI statics::gui;
int main()
{
    statics st;
    st.gui.show();
    
    st.image_resourse.add_image_resource(0, "D:/q.jpg");

    QThread thd;
    MyThread mthd;
    mthd.moveToThread(&thd);
    thd.start();

    QObject::connect(&st.gui, SIGNAL(repaint_signal()), &st.gui, SLOT(repaint_slot()));
    QObject::connect(&mthd, SIGNAL(MyThreadTTRan()), &mthd, SLOT(ran()));

    emit mthd.MyThreadTTRan();

    st.qapp.exec();

    //��ʼ��
    main_game* new_game = new main_game;
    while (new_game->game_mode) {
	    //���������벢��������ֵ
	    new_game->flushed(new_game);
	    //�ƶ����ж���
	    //new_game->crash(new_game);
	    //��Ⲣ����������ײ
	    //new_game->move(new_game);
	    //��ӡ���еĶ���
    }

    return 0;
}