#pragma once

#include <QMainWindow>
#include <qclipboard.h>
#include <qfiledialog.h>
#include "MapCoder.cpp"
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

private:
	Ui::MapEditorClass ui;
	QClipboard* qclipb;
	MapCoder::Map tempmap;

public slots:
	void save_to_clipboard();
	void read_from_clipboard();
	void save_to_file();
	void read_from_file();
};

#endif // !MAPEDITOR_H

