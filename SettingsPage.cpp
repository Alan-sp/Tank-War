#include "SettingsPage.h"
#include <qvalidator.h>
#include "statics.h"
#include "TankWarGUI.h"
#include <QtConcurrent>
#include "main_game.h"
#include <iostream>

SettingsPage::SettingsPage(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	QObject::connect(ui.pushButtonReturn, SIGNAL(clicked()), this, SLOT(back_to_menu()));
	QObject::connect(ui.pushButtonSave, SIGNAL(clicked()), this, SLOT(saveSettings()));

	QIntValidator* valider1 = new QIntValidator(1, 120, this);
	ui.lineEditP1w->setValidator(valider1);
	ui.lineEditP1a->setValidator(valider1);
	ui.lineEditP1s->setValidator(valider1);
	ui.lineEditP1d->setValidator(valider1);
	ui.lineEditP1q->setValidator(valider1);
	ui.lineEditP2w->setValidator(valider1);
	ui.lineEditP2a->setValidator(valider1);
	ui.lineEditP2s->setValidator(valider1);
	ui.lineEditP2d->setValidator(valider1);
	ui.lineEditP2q->setValidator(valider1);
	ui.lineEditBuffDamage->setValidator(new QIntValidator(this));
	ui.lineEditSpawnRate->setValidator(new QIntValidator(this));
	ui.lineEditBulletSpeed->setValidator(new QIntValidator(this));
	ui.lineEditBulletHP->setValidator(new QIntValidator(this));
	ui.lineEditNormalDamage->setValidator(new QIntValidator(this));
	ui.lineEditTankCD->setValidator(new QIntValidator(this));
	ui.lineEditTankHP->setValidator(new QIntValidator(this));
	ui.lineEditTankSpeed->setValidator(new QIntValidator(this));
	ui.lineEditTickTime->setValidator(new QIntValidator(this));
	running = false;
}

SettingsPage::~SettingsPage()
{}

void SettingsPage::syncSettings()
{
	statics st;
	ui.lineEditPlayerA->setText(st.maingame->name1);
	ui.lineEditPlayerB->setText(st.maingame->name2);
	ui.lineEditP1w->setText(QString::number(st.maingame->keybinds1[0]));
	ui.lineEditP1a->setText(QString::number(st.maingame->keybinds1[1]));
	ui.lineEditP1s->setText(QString::number(st.maingame->keybinds1[2]));
	ui.lineEditP1d->setText(QString::number(st.maingame->keybinds1[3]));
	ui.lineEditP1q->setText(QString::number(st.maingame->keybinds1[4]));
	ui.lineEditP2w->setText(QString::number(st.maingame->keybinds2[0]));
	ui.lineEditP2a->setText(QString::number(st.maingame->keybinds2[1]));
	ui.lineEditP2s->setText(QString::number(st.maingame->keybinds2[2]));
	ui.lineEditP2d->setText(QString::number(st.maingame->keybinds2[3]));
	ui.lineEditP2q->setText(QString::number(st.maingame->keybinds2[4]));
	ui.lineEditBuffDamage->setText(QString::number(st.maingame->buffBulletDamage));
	ui.lineEditSpawnRate->setText(QString::number(st.maingame->buffFrequence));
	ui.lineEditBulletSpeed->setText(QString::number(st.maingame->bulletSpeed));
	ui.lineEditBulletHP->setText(QString::number(st.maingame->bulletHP - 1));
	ui.lineEditNormalDamage->setText(QString::number(st.maingame->bulletDamage));
	ui.lineEditTankCD->setText(QString::number(st.maingame->tankCD));
	ui.lineEditTankHP->setText(QString::number(st.maingame->tankHP));
	ui.lineEditTankSpeed->setText(QString::number(st.maingame->tankSpeed));
	ui.lineEditTickTime->setText(QString::number(st.maingame->ticktime));
	running = true;
}

void SettingsPage::checkKeys()
{
	statics st;
	while (running) {
		st.maingame->keyboard_detection();
		QString str;
		for (int i = 0; i < 120; i++) {
			if (st.maingame->down[i] == 1){
				str.append(QString::number(i));
				str.append(',');
			}
		}
		ui.lineEditPressed->setText(str);
		QThread::msleep(100);
	}
}

void SettingsPage::saveSettings()
{
	statics st;
	st.maingame->name1 = ui.lineEditPlayerA->text();
	st.maingame->name2 = ui.lineEditPlayerB->text();
	st.maingame->keybinds1[0] = ui.lineEditP1w->text().toInt();
	st.maingame->keybinds1[1] = ui.lineEditP1a->text().toInt();
	st.maingame->keybinds1[2] = ui.lineEditP1s->text().toInt();
	st.maingame->keybinds1[3] = ui.lineEditP1d->text().toInt();
	st.maingame->keybinds1[4] = ui.lineEditP1q->text().toInt();
	st.maingame->keybinds2[0] = ui.lineEditP2w->text().toInt();
	st.maingame->keybinds2[1] = ui.lineEditP2a->text().toInt();
	st.maingame->keybinds2[2] = ui.lineEditP2s->text().toInt();
	st.maingame->keybinds2[3] = ui.lineEditP2d->text().toInt();
	st.maingame->keybinds2[4] = ui.lineEditP2q->text().toInt();
	st.maingame->buffBulletDamage = ui.lineEditBuffDamage->text().toInt();
	st.maingame->buffFrequence = ui.lineEditSpawnRate->text().toInt();
	st.maingame->bulletSpeed = ui.lineEditBulletSpeed->text().toInt();
	st.maingame->bulletHP = ui.lineEditBulletHP->text().toInt() + 1;
	st.maingame->bulletDamage = ui.lineEditNormalDamage->text().toInt();
	st.maingame->tankCD = ui.lineEditTankCD->text().toInt();
	st.maingame->tankHP = ui.lineEditTankHP->text().toInt();
	st.maingame->tankSpeed = ui.lineEditTankSpeed->text().toInt();
	st.maingame->ticktime= ui.lineEditTickTime->text().toInt();
}

void SettingsPage::back_to_menu() {
	saveSettings();
	running = false;
	statics st;
	st.gamegui->showMainFrame();
}
