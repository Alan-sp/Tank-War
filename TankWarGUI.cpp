#pragma once
#include "statics.h"
#include "TankWarGUI.h"
#include "GameScene.h"
#include "FinishPanel.h"
#include "qpainter.h"
#include "object.h"
#include "MyThread.h"
#include "ui_TankWarGUI.h"
#include "qpainterpath.h"
#include "qtransform.h"
#include <iostream>

TankWarGUI::TankWarGUI(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	statics st;
	gamescene = new GameScene(this);
	finishpanel = new FinishPanel(this);
	QObject::connect(ui.pushButtonStart, SIGNAL(clicked()), this, SLOT(startGame()));
	QObject::connect(this, SIGNAL(game_is_end()), this, SLOT(endGame()));
	gamescene->hide();
	finishpanel->hide();
}

void TankWarGUI::startGame() {
	ui.pushButtonStart->hide();
	ui.pushButtonSetting->hide();
	ui.pushButtonMapEditor->hide();
	statics st;
	st.maingame->init();
	emit st.mthd->MyThreadTTRan();
	gamescene->show();
}

void TankWarGUI::endGame() {
	statics st;
	emit st.mthd->MyThreadTTEnd();
	gamescene->hide();
	finishpanel->analysizeData();
	finishpanel->show();
	st.maingame->clear_pool();
}

TankWarGUI::~TankWarGUI()
{}

void TankWarGUI::showMainFrame()
{
	gamescene->hide();
	finishpanel->hide();
	ui.pushButtonStart->show();
	ui.pushButtonSetting->show();
	ui.pushButtonMapEditor->show();
}

void TankWarGUI::paint_objects(std::list<object*> listz) {//paint all objects in objs
	this->gamescene->paint_objects(listz);
}

void TankWarGUI::repaint_slot() {
	this->repaint();
}