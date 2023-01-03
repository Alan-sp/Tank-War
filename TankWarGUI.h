
#include <QtWidgets/QMainWindow>
#include "ui_TankWarGUI.h"
#include <QMediaPlayer>
#include "object.h"

#ifndef TANKWARGUI_H
#define TANKWARGUI_H

class GameScene;
class FinishPanel;
class SettingsPage;
class MapEditor;

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
	MapEditor* mapeditor;
	QMediaPlayer* startbgm, * gamebgm, * finishbgm;
	Ui::TankWarGUIClass ui;
public slots:
	void repaint_slot();
	void startGame();
	void endGame();
	void openSettings();
	void openMapEditor();
signals:
	void repaint_signal();
	void game_is_end();
	void restart_game();
};

#endif // !TANKWARGUI_H
