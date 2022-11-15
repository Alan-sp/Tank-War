#include "MyThread.h"
#include "statics.h"
void MyThread::ran() {
	statics st;
	this->sleep(1);
	for (int i = 0; i < 10000; i++) {
		printf("%d\n", i);
		this->msleep(20);
		object arr[2] = { object(50,50,i % 360), object(550,50,2*i % 360)};
		st.gui.paint_objects(arr, 2);
	}
}