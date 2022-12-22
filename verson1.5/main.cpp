#pragma once
#include<iostream>
#include<bitset>
#include <QtConcurrent/QtConcurrent>
#include <qthread.h>
#include <QtWidgets/QApplication>

#include "statics.h"
#include "object.h"
#include "bullet.cpp"
#include "main_game.h"
#include "MyThread.h"
#include "wall.cpp"
#include "tank.cpp"
#include "rolling_wall.h"
#include "plane_model.h"
#include "object.cpp"

int arg0 = 1;
int& arg1 = arg0;
char **arg2;

resource_lib statics::resource_library=resource_lib();
QApplication statics::qapp(arg1,arg2);
TankWarGUI statics::gui;

int main(int argc,char *argv[])
{
	statics st;
	st.gui.show();
    st.resource_library.add_image_resource(2, "C:\\Users\\14879\\Pictures\\Tank_War\\tank1.png");
    st.resource_library.add_image_resource(4, "C:\\Users\\14879\\Pictures\\Tank_War\\tank2.png");
    st.resource_library.add_image_resource(3, "C:\\Users\\14879\\Pictures\\Tank_War\\bullet.png");
    st.resource_library.add_image_resource(1, "C:\\Users\\14879\\Pictures\\Tank_War\\wall.png");

	QThread thd;
	MyThread mthd;
//    mthd.ran();
//	mthd.moveToThread(&thd);
//	thd.start();

    QObject::connect(&st.gui, SIGNAL(repaint_signal()), &st.gui, SLOT(repaint_slot()));
//    QObject::connect(&mthd, SIGNAL(MyThreadTTRan()), &mthd, SLOT(ran()));
    main_game now;
//    emit mthd.MyThreadTTRan();

//    st.qapp.exec();
    now.obj_pool.push_back(new tank(100,100,0,2));
    now.obj_pool.push_back(new tank(300,300,0,4));
    now.obj_pool.push_back(new wall(5, 100, 0));
    now.obj_pool.push_back(new wall(1195, 100, 0));
    now.obj_pool.push_back(new wall(5, 300, 0));
    now.obj_pool.push_back(new wall(1195, 300, 0));
    now.obj_pool.push_back(new wall(5, 500, 0));
    now.obj_pool.push_back(new wall(100, 500, 0));
    now.obj_pool.push_back(new wall(5, 700, 0));
    now.obj_pool.push_back(new wall(1195, 700, 0));
    now.obj_pool.push_back(new wall(100, 5, 3.1415926 / 2));
    now.obj_pool.push_back(new wall(100, 795, 3.1415926 / 2));
    now.obj_pool.push_back(new wall(300, 5, 3.1415926 / 2));
    now.obj_pool.push_back(new wall(300, 795, 3.1415926 / 2));
    now.obj_pool.push_back(new wall(500, 5, 3.1415926 / 2));
    now.obj_pool.push_back(new wall(500, 795, 3.1415926 / 2));
    now.obj_pool.push_back(new wall(700, 5, 3.1415926 / 2));
    now.obj_pool.push_back(new wall(700, 795, 3.1415926 / 2));
    now.obj_pool.push_back(new wall(900, 5, 3.1415926 / 2));
    now.obj_pool.push_back(new wall(900, 795, 3.1415926 / 2));
    now.obj_pool.push_back(new wall(1100, 5, 3.1415926 / 2));
    now.obj_pool.push_back(new wall(1100, 795, 3.1415926 / 2));
    now.obj_pool.push_back(new rolling_wall(1000, 200, 10,0.01));
    double tx[4] = { 500,500,-500,-500 }, ty[4] = { 100,-100,-100,100 };//Wall
    double wx[4] = { 100,100,-100,-100 }, wy[4] = { 100,-100,-100,100 };
    plane_model bm(4,wx,wy); plane_model wm(4, tx, ty);
    st.resource_library.add_model_resource(1, wm);
    st.resource_library.add_model_resource(2, bm);
    st.resource_library.add_model_resource(3, bm);
    st.resource_library.add_model_resource(4, bm);
    st.gui.paint_objects(now.obj_pool);
    while(1)
    {
        now.keyboard_detection();
        for (auto i = now.obj_pool.begin(); i != now.obj_pool.end(); i++) {
            auto j = i;
            for (j++;j!=now.obj_pool.end(); j++) {
                collapse_result res = (*i)->collapseWith(**j);
                if (res.isCollapse) {
                    (**i).collapse(*j, -res);
                    (**j).collapse(*i, res);
                    puts("rua");
                }
            }
        }
        st.gui.paint_objects(now.obj_pool);
    }
	return 0;
}
