
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
class MapLoadPage;

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
	MapLoadPage* maploadpage;
	QMediaPlayer* startbgm, * gamebgm, * finishbgm;
	Ui::TankWarGUIClass ui;
public slots:
	void repaint_slot();
	void startGame();
	void endGame();
	void openSettings();
	void openMapLoad();
	void openMapEditor();
	void pauseGame();
	void unpauseGame();
	void return_to_menu();
signals:
	void repaint_signal();
	void game_is_end();
	void game_is_paused();
	void restart_game();
};

#endif // !TANKWARGUI_H
