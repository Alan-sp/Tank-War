
#include <QWidget>
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

public slots:
	void returnToMainFrame();
};


#endif // !FINISHPANEL_H
