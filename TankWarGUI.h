#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_TankWarGUI.h"
#include "object.cpp"

class TankWarGUI : public QMainWindow
{
    Q_OBJECT

public:
	
	TankWarGUI(QWidget *parent = nullptr);
	~TankWarGUI();

	void paint_objects(object objs[],int n);
protected:
	void paintEvent(QPaintEvent* event);

private:

	int n;
	object objs[10010];

	Ui::TankWarGUIClass ui;
public slots:
	void repaint_slot();
signals:
	void repaint_signal();
};
