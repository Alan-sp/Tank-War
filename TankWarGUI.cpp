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
#include "MapLoadPage.h"
#include "qtransform.h"
#include "SettingsPage.h"
#include "MapEditor.h"
#include "qmediaplayer.h"
#include <QMediaPlayer>
#include <QApplication>
#include <QUrl>
#include <QtConcurrent>
#include <iostream>

TankWarGUI::TankWarGUI(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	this->setFixedSize(1200, 800);
	this->setWindowFlags(windowFlags() & ~Qt::WindowMaximizeButtonHint);
	statics st;
	gamescene = new GameScene(this);
	finishpanel = new FinishPanel(this);
	settingpage = new SettingsPage(this);
	mapeditor = new MapEditor();
	maploadpage = new MapLoadPage(this);
	startbgm = new QMediaPlayer();
	gamebgm = new QMediaPlayer();
	startbgm->setSource(QUrl::fromLocalFile("D:/Resforgame/start.mp3"));
	gamebgm->setSource(QUrl::fromLocalFile("D:/Resforgame/game.mp3"));
	startbgm->play();
	QObject::connect(ui.pushButtonStart, SIGNAL(clicked()), this, SLOT(openMapLoad()));
	QObject::connect(ui.pushButtonSetting, SIGNAL(clicked()), this, SLOT(openSettings()));
	QObject::connect(ui.pushButtonMapEditor, SIGNAL(clicked()), this, SLOT(openMapEditor()));
	QObject::connect(this, SIGNAL(game_is_end()), this, SLOT(endGame()));
	QObject::connect(this, SIGNAL(restart_game()), this, SLOT(startGame()));
	QObject::connect(ui.pushButtonResume, SIGNAL(clicked()), this, SLOT(unpauseGame()));
	QObject::connect(ui.pushButtonReturn, SIGNAL(clicked()), this, SLOT(return_to_menu()));
	QObject::connect(this, SIGNAL(game_is_paused()), this, SLOT(pauseGame()));
	gamescene->hide();
	finishpanel->hide();
	settingpage->hide();
	mapeditor->hide();
	maploadpage->hide();
	ui.pushButtonResume->hide();
	ui.pushButtonReturn->hide();
}

void TankWarGUI::startGame() {
	ui.pushButtonStart->hide();
	ui.pushButtonSetting->hide();
	ui.pushButtonMapEditor->hide();
	this->setFocus();
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
	this->setFocus();
}

void TankWarGUI::openSettings()
{
	ui.pushButtonStart->hide();
	ui.pushButtonSetting->hide();
	ui.pushButtonMapEditor->hide();
	settingpage->syncSettings();
	QFuture<void> future	= QtConcurrent::run(&SettingsPage::checkKeys, settingpage);
	settingpage->show();
	this->setFocus();
}

void TankWarGUI::openMapLoad()
{
	ui.pushButtonStart->hide();
	ui.pushButtonSetting->hide();
	ui.pushButtonMapEditor->hide();
	gamebgm->play();
	maploadpage->show();
	this->setFocus();
}

void TankWarGUI::openMapEditor()
{
	mapeditor->show();
	this->setFocus();
}

void TankWarGUI::pauseGame()
{
	gamescene->hide();
	this->setFocus();
	ui.pushButtonResume->show();
	ui.pushButtonReturn->show();
}

void TankWarGUI::unpauseGame()
{
	statics st;
	emit st.mthd->MyThreadTTRan();
	gamescene->show();
	this->setFocus();
	ui.pushButtonResume->hide();
	ui.pushButtonReturn->hide();
}

void TankWarGUI::return_to_menu()
{
	statics st;
	st.maingame->clear_pool();
	this->setFocus();
	showMainFrame();
}

TankWarGUI::~TankWarGUI()
{}

void TankWarGUI::showMainFrame()
{
	gamescene->hide();
	maploadpage->hide();
	finishpanel->hide();
	settingpage->hide();
	ui.pushButtonResume->hide();
	ui.pushButtonReturn->hide();
	ui.pushButtonStart->show();
	ui.pushButtonSetting->show();
	ui.pushButtonMapEditor->show();
	this->setFocus();
}

void TankWarGUI::paint_objects(std::list<object*> listz) {//paint all objects in objs
	this->gamescene->paint_objects(listz);
}

void TankWarGUI::repaint_slot() {
	this->repaint();
	this->setFocus();
}
