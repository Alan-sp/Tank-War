#pragma once
#include "MyThread.h"
#include "statics.h"
#include "rolling_wall.h"
#include "tank.cpp"
#include "wall.cpp"
#include "bullet.cpp"
#include "main_game.h"
#include "main_game.cpp"
#include <ctime>
#include <iostream>
void MyThread::ran() {

//	sleep(5);
	srand(time(NULL));

	statics st;
    main_game now;
	std::list<object*> listz;

    listz.push_back(new tank(10,10,0,2));
    listz.push_back(new tank(300,300,0,4));
	listz.push_back(new wall(5, 100, 0));
	listz.push_back(new wall(1195, 100, 0));
	listz.push_back(new wall(5, 300, 0));
	listz.push_back(new wall(1195, 300, 0));
	listz.push_back(new wall(5, 500, 0));
	listz.push_back(new wall(1195, 500, 0));
	listz.push_back(new wall(5, 700, 0));
	listz.push_back(new wall(1195, 700, 0));
	listz.push_back(new wall(100, 5, 3.1415926 / 2));
	listz.push_back(new wall(100, 795, 3.1415926 / 2));
	listz.push_back(new wall(300, 5, 3.1415926 / 2));
	listz.push_back(new wall(300, 795, 3.1415926 / 2));
	listz.push_back(new wall(500, 5, 3.1415926 / 2));
	listz.push_back(new wall(500, 795, 3.1415926 / 2));
	listz.push_back(new wall(700, 5, 3.1415926 / 2));
	listz.push_back(new wall(700, 795, 3.1415926 / 2));
	listz.push_back(new wall(900, 5, 3.1415926 / 2));
	listz.push_back(new wall(900, 795, 3.1415926 / 2));
	listz.push_back(new wall(1100, 5, 3.1415926 / 2));
	listz.push_back(new wall(1100, 795, 3.1415926 / 2));

	listz.push_back(new rolling_wall(200, 200, 1, 0.05));
	listz.push_back(new wall(500, 500, 3));
	listz.push_back(new rolling_wall(200, 500, 9,-0.03));
	listz.push_back(new wall(700, 700, 5));
	listz.push_back(new rolling_wall(1000, 200, 10,0.01));

	double tx[4] = { 5,5,-5,-5 }, ty[4] = { 100,-100,-100,100 };//Wall
	double wx[4] = { 5,5,-5,-5 }, wy[4] = { 5,-5,-5,5 };
	plane_model bm(4,wx,wy); plane_model wm(4, tx, ty);
	st.resource_library.add_model_resource(1, wm);
	st.resource_library.add_model_resource(3, bm);
    st.resource_library.add_image_resource(2, "C:\\Users\\14879\\Pictures\\Tank_War\\tank1.png");
    st.resource_library.add_image_resource(4, "C:\\Users\\14879\\Pictures\\Tank_War\\tank2.png");
    st.resource_library.add_image_resource(3, "C:\\Users\\14879\\Pictures\\Tank_War\\bullet.png");
	long timeused=0,starttime,standardTickTime=15;
	while (true) {
        st.gui.paint_objects(listz);
		if (timeused < standardTickTime){
			msleep(standardTickTime - timeused);
			timeused = 0;
		}
		else if (timeused < 200) {
			timeused -= standardTickTime;
			std::cout << "Lagging" << std::endl;
		}
		else {
			std::cout << "Can't keep up:Running " << timeused << " behind!!" << std::endl;
			timeused = 0;
		}
			
		starttime = clock()+timeused;
		for (auto i = listz.begin(); i != listz.end(); i++) {
			auto j = i;
			for (j++;j!=listz.end(); j++) {
				collapse_result res = (*i)->collapseWith(**j);
				if (res.isCollapse) {
					(**i).collapse(*j, -res);
					(**j).collapse(*i, res);
				}
			}
		}
		for (auto i = listz.begin(); i != listz.end();) {
            (**i).ticking(1);
			if ((*i)->get_state() == -1)
				i = listz.erase(i);
			else
				i++;
		}
		timeused = clock() - starttime;
	}
}
