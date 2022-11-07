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

    void paint_objects(object objs[]);

private:
    Ui::TankWarGUIClass ui;
};
