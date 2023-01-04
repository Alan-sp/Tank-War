#pragma once

#include <QWidget>
#include "ui_MapLoadPage.h"

#ifndef MAPLOADPAGE_H
#define MAPLOADPAGE_H

class MapLoadPage : public QWidget
{
	Q_OBJECT

public:
	MapLoadPage(QWidget* parent = nullptr);
	~MapLoadPage();

private:
	Ui::MapLoadPageClass ui;
public slots:
	void fromClipboard();
	void fromFile();
	void randomGenerate();
	void return_to_menu();
	void startGame();
};


#endif // !MAPLOADPAGE_H


