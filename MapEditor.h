#pragma once

#include <QMainWindow>
#include "object.h"
#include <QMouseEvent>
#include <qclipboard.h>
#include <qfiledialog.h>
#include <qmutex.h>
#include "MapCoder.cpp"
#include <map>
#include <qmessagebox.h>
#include "ui_MapEditor.h"

#ifndef MAPEDITOR_H
#define MAPEDITOR_H

class MapEditor : public QMainWindow
{
	Q_OBJECT

public:
	MapEditor(QWidget* parent = nullptr);
	~MapEditor();

	void paintEvent(QPaintEvent* event);
	void mousePressEvent(QMouseEvent* event);
	void wheelEvent(QWheelEvent* event);

private:
	Ui::MapEditorClass ui;
	QClipboard* qclipb;
	MapCoder::Map tempmap;
	QMutex lock;
	bool attentionSelected;
	int selectedIndex,selectedType;
	int totalIndex = 0, total[10];
	object* selected;
	std::map<int, object*> objs;
	QListWidgetItem* selectedItem;
	QIntValidator* bfvalidator;
	QDoubleValidator* rwvalidator;

	void loadFromMap();
	void syncToMap();
	void syncToSelection();
	void attentionToSelected();

public slots:
	void save_to_clipboard();
	void read_from_clipboard();
	void save_to_file();
	void read_from_file();
	void selectionChanged(QListWidgetItem*);
	void removeObject();
	void syncSelectionText();
	void addWall();
	void addRollingWall();
	void addBuff();
	void addSpawn();
	void randomMap();
	void addShortWall();
	void addMidWall();
	void addMovableBlock();
	void addTriangle();
};

#endif // !MAPEDITOR_H

