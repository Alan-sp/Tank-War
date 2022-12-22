#pragma once
#include "TankWarGUI.h"
#include "qpainter.h"
#include "object.h"
#include "statics.h"
#include "ui_TankWarGUI.h"
#include "qpainterpath.h"
#include "qtransform.h"
#include <iostream>

TankWarGUI::TankWarGUI(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	painting = false;
	statics st;
	QObject::connect(ui.pushButtonStart, SIGNAL(clicked()), &st.gui, SLOT(startGame()));
}

void TankWarGUI::startGame() {
	ui.pushButtonStart->setVisible(false);
	ui.pushButtonSetting->setVisible(false);
	statics st;
	emit st.mthd.MyThreadTTRan();
}

TankWarGUI::~TankWarGUI()
{}

void TankWarGUI::paintEvent(QPaintEvent* event) {
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing, true);
	statics st;
	QPainterPath qpa;
	qpa.addRect(0, 0, 1200, 900);
	painter.fillPath(qpa, Qt::black);
	painting = true;
	for (auto i = objs.begin(); i != objs.end(); i++){
		QTransform trans;
		trans.rotate((**i).get_direction() * 180 / 3.1415926 - 90, Qt::ZAxis);
		QPixmap pic = st.resource_library.get_image((**i).get_state()).transformed(trans);
		painter.drawPixmap((**i).get_x()-pic.width()/2, (**i).get_y()-pic.height()/2, pic.width(), pic.height(), pic);
	}
	painting = false;
}

void TankWarGUI::paint_objects(std::list<object*> listz) {//paint all objects in objs
	this->objs.clear();
	this->objs = listz;
	if(!painting)emit repaint_signal();
}

void TankWarGUI::repaint_slot() {
	this->repaint();
}