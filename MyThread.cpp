#pragma once
#include "MyThread.h"
#include "statics.h"
#include "tank.cpp"
void MyThread::ran() {
	statics st;
	this->sleep(1);
	for (int i = 0; i < 10000; i++) {
		//printf("%d %.6lf\n", i, 3.14159265357 / 180 * i);
		this->msleep(20);
		tank a(50, 50, 3.14159265357 / 180 * i), b(550, 50, 3.14159265357 / 180 * i *2);
		tank* pa = &a, * pb = &b;
		object *arr[2] = { pa, pb};
		st.gui.paint_objects(arr, 2);
	}
}