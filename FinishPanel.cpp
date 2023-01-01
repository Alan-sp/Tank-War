#pragma once
#include "FinishPanel.h"
#include "TankWarGUI.h"
#include "resource_lib.h"
#include "main_game.h"
#include "statics.h"

#include <algorithm>

FinishPanel::FinishPanel(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	QObject::connect(ui.pushButtonReturn, SIGNAL(clicked()), this, SLOT(returnToMainFrame()));
}

FinishPanel::~FinishPanel()
{}

void FinishPanel::analysizeData()
{
	statics st;
	tank* winner = static_cast<tank*> (st.maingame->winner);
	ui.winnerImg->setPixmap(st.resource_library->get_image(20 + winner->name));
	//0
	char str[2010];
	snprintf(str, 2000, "%s 发射了%d枚炮弹，其中%d枚命中", winner->strname, winner->shootcount,winner->hitcount);
	ui.interestringLabel1->setText(str);
}

void FinishPanel::returnToMainFrame() {
	statics st;
	this->hide();
	st.gamegui->showMainFrame();
}