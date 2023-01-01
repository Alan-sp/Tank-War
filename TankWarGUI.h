
#include <QtWidgets/QMainWindow>
#include "ui_TankWarGUI.h"
#include "object.h"

#ifndef TANKWARGUI_H
#define TANKWARGUI_H

class GameScene;
class FinishPanel;
class SettingsPage;

class TankWarGUI : public QMainWindow
{
	Q_OBJECT

public:

	TankWarGUI(QWidget* parent = nullptr);
	~TankWarGUI();

	void paint_objects(std::list<object*> listz);
	void showMainFrame();

private:
	GameScene* gamescene;
	FinishPanel* finishpanel;
	SettingsPage* settingpage;
	Ui::TankWarGUIClass ui;
public slots:
	void repaint_slot();
	void startGame();
	void endGame();
	void openSettings();
signals:
	void repaint_signal();
	void game_is_end();
};

#endif // !TANKWARGUI_H
