#include <QWidget>
#include "ui_SettingsPage.h"

#ifndef SETTINGSPAGE_H
#define SETTINGSPAGE_H

class SettingsPage : public QWidget
{
	Q_OBJECT

public:
	SettingsPage(QWidget* parent = nullptr);
	~SettingsPage();

	void syncSettings();
	void checkKeys();
private:
	bool running;
	Ui::SettingsPageClass ui;
public slots:
	void back_to_menu();
	void saveSettings();
};

#endif // !SETTINGSPAGE_H
