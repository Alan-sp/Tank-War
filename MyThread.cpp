#pragma once
#include "MyThread.h"
#include "statics.h"
#include "tank.cpp"
#include "wall.cpp"
#include "bullet.cpp"
void MyThread::ran() {
	statics st;
	wall w1(5, 100, 0);
	wall w2(195, 100, 0);
	wall w3(100, 5, 3.1415926/2);
	wall w4(100, 195, 3.1415926/2);
	bullet b(150, 50, 1, 0);
	bullet c(50, 50, 2, 0);
	object* arr[6] = { &c,&b,&w1,&w2,&w3,&w4 };
	double tx[4] = { 5,5,-5,-5 }, ty[4] = { 100,-100,-100,100 };//Wall
	double wx[4] = { 5,5,-5,-5 }, wy[4] = { 5,-5,-5,5 };
	plane_model bm(5); plane_model wm(4, tx, ty);
	st.resource_library.add_model_resource(1, wm);
	st.resource_library.add_model_resource(3, bm);
	st.resource_library.add_image_resource(1, "D:/Resforgame/w.jpg");
	st.resource_library.add_image_resource(3, "D:/Resforgame/b.jpg");

	while (true) {
		st.gui.paint_objects(arr, 6);
		msleep(20);
		for (int i = 0; i < 6; i++) {
			for (int j = i + 1; j < 6; j++) {
				collapse_result res = arr[i]->collapseWith(*arr[j]);
				if (res.isCollapse) {
					(*arr[i]).collapse(arr[j], -res);
					(*arr[j]).collapse(arr[i], res);
				}
			}
		}
		for (int i = 0; i < 5; i++) {
			(*arr[i]).ticking();
		}
	}
}