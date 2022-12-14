#include "statics.h"
#include "MyThread.h"
#include "TankWarGUI.h"
#include "rolling_wall.h"
#include "tank.cpp"
#include "wall.cpp"
#include "bullet.cpp"
#include <ctime>
#include <iostream>
#include "buff.cpp"

#ifndef MYTHREAD_CPP
#define MYTHREAD_CPP

void MyThread::ran() {
	statics st;
	long timeused = 0, starttime, standardTickTime = st.maingame->ticktime,finishDelay=0;
	running = true;
	while (running) {
		st.gamegui->paint_objects(st.maingame->obj_pool);
		if (timeused < standardTickTime) {
			msleep(standardTickTime - timeused);
			timeused = 0;
		}
		else if (timeused < 200) {
			timeused -= standardTickTime;
			std::cout << "Lagging" << std::endl;
		}
		else {
			std::cout << "Can't keep up:Running " << timeused << "ms behind!!" << std::endl;
			timeused = 0;
		}

		starttime = clock() + timeused;
		for (auto i = st.maingame->obj_pool.begin(); i != st.maingame->obj_pool.end(); i++) {
			auto j = i;
			for (j++; j != st.maingame->obj_pool.end(); j++) {
				collapse_result res = (*i)->collapseWith(**j);
				if (res.isCollapse) {
					res.normalize();
					(*i)->collapse(*j, res.opposide());
					(*j)->collapse(*i, res);
				}
			}
		}

		if (rand() % st.maingame->buffFrequence == 0 )st.maingame->add_object(new buff());

		st.maingame->keyboard_detection();

		if (st.maingame->down[27]) {
			emit st.gamegui->game_is_paused();
			return;
		}

		for (auto i = st.maingame->obj_pool.begin(); i != st.maingame->obj_pool.end();) {
			(**i).ticking();
			if ((*i)->get_state() == -1)
			{
				delete *i;
				i = st.maingame->obj_pool.erase(i);
			}
			else
				i++;
		}
		timeused = clock() - starttime;
		if (st.maingame->tank_num < 2&&finishDelay==0) {
			for (auto i = st.maingame->obj_pool.begin(); i != st.maingame->obj_pool.end(); i++)
				if ((*i)->get_state() / 10 == 2) {
					tank* p = dynamic_cast<tank*>(*i);
					st.maingame->winner = new tank(*p);
					break;
				}
			finishDelay = 1;
		}
		if (finishDelay)finishDelay++;
		if (finishDelay==100) {
			emit st.gamegui->game_is_end();
			running = false;
		}
	}
}

void MyThread::stoq()
{
	running = false;
}


#endif // !MYTHREAD_CPP
