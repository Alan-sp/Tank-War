
#include <qthread.h>

#ifndef  MYTHREAD_H
#define MYTHREAD_H

class MyThread :public QThread {
	Q_OBJECT
public:
	explicit MyThread(QObject* parent = 0) {}
	~MyThread() {}
private:
	bool running = true;
public slots:
	void ran();
	void stoq();
signals:
	void MyThreadTTRan();
	void MyThreadTTEnd();
};
#endif // ! MYTHREAD_H
