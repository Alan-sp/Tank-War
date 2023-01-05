
#include <QWidget>
#include <QMediaPlayer>
#include <QApplication>
#include "ui_FinishPanel.h"
#include "tank.cpp"

#ifndef FINISHPANEL_H
#define FINISHPANEL_H

class FinishPanel : public QWidget
{
	Q_OBJECT

public:
	FinishPanel(QWidget* parent = nullptr);
	~FinishPanel();

	void analysizeData();
private:
	Ui::FinishPanelClass ui;
	QMediaPlayer* finishbgm;
	void removeObjs();
public slots:
	void returnToMainFrame();
	void restartGame();
};


#endif // !FINISHPANEL_H
