#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_TankWarGUI.h"
#include "object.h"

class TankWarGUI : public QMainWindow
{
    Q_OBJECT

public:
	
	TankWarGUI(QWidget *parent = nullptr);
	~TankWarGUI();

	void paint_objects(std::list<object*> listz);
protected:
	void paintEvent(QPaintEvent* event);

private:
	std::list<object*> objs;
	bool painting;
	Ui::TankWarGUIClass ui;
public slots:
	void repaint_slot();
signals:
	void repaint_signal();
};
