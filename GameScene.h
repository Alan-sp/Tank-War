#include <qwidget.h>
#include "object.h"
#include <qmutex.h>

#ifndef GAMESCENE_H
#define GAMESCENE_H

class GameScene :
	public QWidget
{
	Q_OBJECT
public:

	GameScene(QWidget* parent = nullptr);
	~GameScene();

	void paint_objects(std::list<object*>& listz);
protected:
	void paintEvent(QPaintEvent* event);

private:
	std::list<object*> objs;
	QMutex lock;
	QMutex lock2;
public slots:
	void repaint_slot();
signals:
	void repaint_signal();
};


#endif // !GAMESCENE_H
