#include "GameScene.h"
#pragma once
#include "qpainter.h"
#include "object.h"
#include "statics.h"
#include "resource_lib.h"
#include "qpainterpath.h"
#include "qtransform.h"
#include <iostream>

GameScene::GameScene(QWidget* parent)
	: QWidget(parent)
{
	statics st;
	this->setFixedSize(1200, 800);
	QObject::connect(this, SIGNAL(repaint_signal()), this, SLOT(repaint_slot()));
}

GameScene::~GameScene()
{}

void GameScene::paintEvent(QPaintEvent* event) {
	lock2.lock();
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing, true);
	statics st;
	QPainterPath qpa;
	qpa.addRect(0, 0, 1200, 800);
	painter.fillPath(qpa, Qt::black);
	for (auto i = objs.begin(); i != objs.end();) {
		QTransform trans;
		trans.rotate((**i).get_direction() * 180 / 3.1415926 - 90, Qt::ZAxis);
		QPixmap pic = st.resource_library->get_image((**i).get_state()).transformed(trans);
		painter.drawPixmap((**i).get_x() - pic.width() / 2, (**i).get_y() - pic.height() / 2, pic.width(), pic.height(), pic);
		if (i != objs.end())i++;
	}
	lock2.unlock();
}

void GameScene::paint_objects(std::list<object*> & listz) {//paint all objects in objs
	if (!lock.tryLock())return;
	this->objs = listz;
	emit repaint_signal();
	lock.unlock();
}

void GameScene::repaint_slot() {
	this->repaint();
}