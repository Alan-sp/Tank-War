#pragma once
#include <qthread.h>

class MyThread :public QThread {
	Q_OBJECT
public:
	explicit MyThread(QObject* parent = 0) {}
	~MyThread() {}
public slots:
	void ran();
signals:
	void MyThreadTTRan();
};