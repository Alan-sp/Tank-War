#pragma once
#include "statics.h"
#include "TankWarGUI.h"
#include "ui_TankWarGUI.h"
#include "GameScene.h"
#include "FinishPanel.h"
#include "qpainter.h"
#include "object.h"
#include "MyThread.h"
#include "qpainterpath.h"
#include "qtransform.h"
#include "SettingsPage.h"
#include <QtConcurrent>
#include <iostream>

TankWarGUI::TankWarGUI(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	statics st;
	gamescene = new GameScene(this);
	finishpanel = new FinishPanel(this);
	settingpage = new SettingsPage(this);
	QObject::connect(ui.pushButtonStart, SIGNAL(clicked()), this, SLOT(startGame()));
	QObject::connect(ui.pushButtonSetting, SIGNAL(clicked()), this, SLOT(openSettings()));
	QObject::connect(this, SIGNAL(game_is_end()), this, SLOT(endGame()));
	gamescene->hide();
	finishpanel->hide();
	settingpage->hide();
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

void TankWarGUI::openSettings()
{
	ui.pushButtonStart->hide();
	ui.pushButtonSetting->hide();
	ui.pushButtonMapEditor->hide();
	settingpage->syncSettings();
	QFuture<void> future	= QtConcurrent::run(&SettingsPage::checkKeys, settingpage);
	settingpage->show();
}

TankWarGUI::~TankWarGUI()
{}

void TankWarGUI::showMainFrame()
{
	gamescene->hide();
	finishpanel->hide();
	settingpage->hide();
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