#pragma once
#include "MyThread.h"
#include "statics.h"
#include "rolling_wall.h"
#include "tank.cpp"
#include "wall.cpp"
#include "bullet.cpp"
#include <ctime>
#include <iostream>
void MyThread::ran() {

	sleep(2);
	srand(time(NULL));

	statics st;
	long timeused=0,starttime,standardTickTime=15;
	while (true) {
		st.gui.paint_objects(st.maingame.obj_pool);
		if (timeused < standardTickTime){
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
			
		starttime = clock()+timeused;
		for (auto i = st.maingame.obj_pool.begin(); i != st.maingame.obj_pool.end(); i++) {
			auto j = i;
			for (j++;j!=st.maingame.obj_pool.end(); j++) {
				collapse_result res = (*i)->collapseWith(**j);
				if (res.isCollapse) {
					(*i)->collapse(*j, res.opposide());
					(*j)->collapse(*i, res);
				}
			}
		}
		st.maingame.keyboard_detection();
		for (auto i = st.maingame.obj_pool.begin(); i != st.maingame.obj_pool.end();) {
			(**i).ticking();
			if ((*i)->get_state() == -1)
				i = st.maingame.obj_pool.erase(i);
			else
				i++;
		}
		timeused = clock() - starttime;
	}
}