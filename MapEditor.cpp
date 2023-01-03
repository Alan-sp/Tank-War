﻿#include "MapEditor.h"
#include <fstream>
#include <qpainter.h>
#include <qpainterpath.h>
#include "resource_lib.h"
#include "statics.h"
#include <sstream>

MapEditor::MapEditor(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	this->setFixedSize(1300, 800);

	qclipb = QApplication::clipboard();

	rwvalidator = new QDoubleValidator();
	bfvalidator = new QIntValidator(1, 4);
	ui.lineEditDirect->setValidator(rwvalidator);
	ui.lineEditX->setValidator(rwvalidator);
	ui.lineEditY->setValidator(rwvalidator);

	QObject::connect(ui.actionCopyToClipboard, SIGNAL(triggered()), this, SLOT(save_to_clipboard()));
	QObject::connect(ui.actionReadFromClipboard, SIGNAL(triggered()), this, SLOT(read_from_clipboard()));
	QObject::connect(ui.actionSaveToFile, SIGNAL(triggered()), this, SLOT(save_to_file()));
	QObject::connect(ui.actionReadFromFile, SIGNAL(triggered()), this, SLOT(read_from_file()));
	QObject::connect(ui.listWidget, SIGNAL(itemActivated(QListWidgetItem*)), this, SLOT(selectionChanged(QListWidgetItem*)));
	QObject::connect(ui.pushButtonRemove, SIGNAL(clicked()), this, SLOT(removeObject()));
	QObject::connect(ui.pushButtonSync, SIGNAL(clicked()), this, SLOT(syncSelectionText()));
	QObject::connect(ui.actionPartWall, SIGNAL(triggered()), this, SLOT(addWall()));
	QObject::connect(ui.actionPartRollingWall, SIGNAL(triggered()), this, SLOT(addRollingWall()));
	QObject::connect(ui.actionBuff, SIGNAL(triggered()), this, SLOT(addBuff()));
	QObject::connect(ui.actionTankSpawn, SIGNAL(triggered()), this, SLOT(addSpawn()));

	this->repaint();
}

MapEditor::~MapEditor()
{}

void MapEditor::paintEvent(QPaintEvent* event) {
	lock.lock();
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing, true);
	statics st;
	QPainterPath qpa;
	qpa.addRect(0, 0, 1200, 800);
	painter.fillPath(qpa, Qt::black);
	for (auto i = objs.begin(); i != objs.end();) {
		QTransform trans;
		trans.rotate((*i).second->get_direction() * 180 / 3.1415926 - 90, Qt::ZAxis);
		QPixmap pic = st.resource_library->get_image((*i).second->get_state()).transformed(trans);
		painter.drawPixmap((*i).second->get_x() - pic.width() / 2, (*i).second->get_y() - pic.height() / 2, pic.width(), pic.height(), pic);
		if (i != objs.end())i++;
	}
	lock.unlock();
}

void MapEditor::mousePressEvent(QMouseEvent* event)
{
	if (selectedType > 0 && selectedIndex > 0 && selected != NULL && (event->buttons() & Qt::LeftButton)) {
		if (event->x() < 1200) {
			ui.lineEditX->setText(QString::number(event->x()));
			ui.lineEditY->setText(QString::number(event->y()));
			syncToSelection();
			this->repaint();
			event->accept();
		}
	}
}

void MapEditor::wheelEvent(QWheelEvent* event)
{
	if (selectedType > 0 && selectedIndex > 0 && selected != NULL) {
		if (event->position().x() < 1200) {
			if (event->angleDelta().y() > 0)
				ui.lineEditDirect->setText(QString::number(selected->get_direction() + 0.01));
			else
				ui.lineEditDirect->setText(QString::number(selected->get_direction() - 0.01));
			syncToSelection();
			this->repaint();
			event->accept();
		}
	}
}

void MapEditor::save_to_clipboard() {
	syncToMap();
	qclipb->setText(QString::fromStdString(MapCoder::encode(tempmap)));
	this->repaint();
}

void MapEditor::loadFromMap()
{
	selected = NULL,selectedIndex=-1,selectedType=-1;
	selectionChanged(NULL);
	for (auto i = objs.begin(); i != objs.end();) {
		delete (*i).second;
		if (i != objs.end())i++;
	}
	objs.clear();
	ui.listWidget->clear();
	totalIndex = 0, totalWall = 0, totalRollingWall = 0, totalBuff = 0, totalTank = 0;
	QListWidgetItem* p;
	for (auto i = tempmap.objs.begin(); i != tempmap.objs.end(); i++) {
		objs[++totalIndex] = *i;
		std::ostringstream oss("");
		if (wall* p = dynamic_cast<wall*>(*i)) {
			oss << "Wall" << totalWall; totalWall++;
		}
		else if (rolling_wall* p = dynamic_cast<rolling_wall*>(*i)) {
			oss << "RollingWall" << totalRollingWall; totalRollingWall++;
		}
		else if (buff* p = dynamic_cast<buff*>(*i)) {
			oss << "Buff" << totalBuff; totalBuff++;
		}
		p = new QListWidgetItem(QString::fromStdString(oss.str()));
		p->setData(1, totalIndex);
		ui.listWidget->addItem(p);
	}
	for (auto i = tempmap.spawns.begin(); i != tempmap.spawns.end(); i++) {
		objs[++totalIndex] = new tank((*i).x, (*i).y, (*i).dir, 1, 0, 0, 0, 0, 0, "Spawn");
		std::ostringstream oss("");
		oss << "TankSpawn" << totalTank; totalTank++;
		p = new QListWidgetItem(QString::fromStdString(oss.str()));
		p->setData(1, totalIndex);
		ui.listWidget->addItem(p);
	}
}

void MapEditor::syncToMap()
{
	tempmap.objs.clear();
	tempmap.spawns.clear();
	for (auto j = objs.begin(); j != objs.end();) {
		auto i = (*j).second;
		if (tank* p = dynamic_cast<tank*>(i)) {
			MapCoder::Point point;
			point.x = i->get_x(), point.y = i->get_y(), point.dir = i->get_direction();
			tempmap.spawns.push_back(point);
		}
		else
			tempmap.objs.push_back(i);
		if (j != objs.end())j++;
	}
}

void MapEditor::syncToSelection()
{
	double xx = ui.lineEditX->text().toDouble(), yy = ui.lineEditY->text().toDouble(), dir = ui.lineEditDirect->text().toDouble(), wspeed;
	int type;
	object* p = NULL;
	switch (selectedType)
	{
	case 1:
		p = new wall(xx, yy, dir);

		break;
	case 2:
		wspeed = ui.lineEditSA->text().toDouble();
		p = new rolling_wall(xx, yy, dir, wspeed);
		break;
	case 3:
		type = ui.lineEditSA->text().toInt();
		p = new buff(xx, yy, dir, type);
		break;
	case 4:
		p = new tank(xx, yy, dir, 1, 0, 0, 0, 0, 0, "Spawn");
		break;
	default:
		break;
	}
	objs.erase(selectedIndex);
	delete selected;
	objs[selectedIndex] = p, selected = p;
}

void MapEditor::read_from_clipboard()
{
	tempmap = MapCoder::decode(qclipb->text().toStdString());
	loadFromMap();
	this->repaint();
}

void MapEditor::save_to_file()
{
	syncToMap();
	QString filename = QFileDialog::getSaveFileName(this, "保存到", ".", "*");
	std::ofstream ofs(filename.toStdString(),std::ios::out);
	if (!ofs) {
		QMessageBox::critical(this, "错误", "无法打开文件");
		return;
	}
	ofs << MapCoder::encode(tempmap);
	ofs.flush();
	ofs.close();
	this->repaint();
}

void MapEditor::read_from_file()
{
	QString filename = QFileDialog::getOpenFileName(this, "打开", ".", "*");
	std::ifstream ifs(filename.toStdString(), std::ios::in);
	if (!ifs) {
		QMessageBox::critical(this, "错误", "无法打开文件");
		return;
	}
	std::istreambuf_iterator<char> beg(ifs), end;
	std::string strdata(beg, end);
	ifs.close();
	tempmap = MapCoder::decode(strdata);
	loadFromMap();
	this->repaint();
}

void MapEditor::selectionChanged(QListWidgetItem* item)
{
	if (item != NULL)
	{
		selectedIndex = item->data(1).toInt(), selected = objs[selectedIndex], selectedItem = item;
		ui.lineEditX->setText(QString::number(selected->get_x()));
		ui.lineEditY->setText(QString::number(selected->get_y()));
		ui.lineEditDirect->setText(QString::number(selected->get_direction()));
		if (wall* p = dynamic_cast<wall*>(selected)) {
			ui.labelObjName->setText("Wall");
			ui.labelSpecialSettingName->setText("None");
			selectedType = 1;
		}
		else if (rolling_wall* p = dynamic_cast<rolling_wall*>(selected)) {
			ui.labelObjName->setText("RollingWall");
			ui.labelSpecialSettingName->setText("旋转速度");
			ui.lineEditSA->setText(QString::number(p->rolling_speed));
			ui.lineEditSA->setValidator(rwvalidator);
			selectedType = 2;
		}
		else if (buff* p = dynamic_cast<buff*>(selected)) {
			ui.labelObjName->setText("Buff");
			ui.labelSpecialSettingName->setText("Buff类型");
			ui.lineEditSA->setText(QString::number(p->buff_state));
			ui.lineEditSA->setValidator(bfvalidator);
			selectedType = 3;
		}else if (tank* p = dynamic_cast<tank*>(selected)) {
			ui.labelObjName->setText("TankSpawn");
			ui.labelSpecialSettingName->setText("None");
			selectedType = 4;
		}
	}
	else {
		selectedIndex = -1, selected = NULL, selectedItem = NULL;
		ui.lineEditX->clear();
		ui.lineEditY->clear();
		ui.lineEditDirect->clear();
		ui.lineEditSA->clear();
		ui.labelSpecialSettingName->setText("None");
	}
}

void MapEditor::removeObject()
{
	if (selected != NULL)
	{
		objs.erase(selectedIndex);
		ui.listWidget->takeItem(ui.listWidget->indexFromItem(selectedItem).row());
		delete selected;
	}
	selected = NULL, selectedIndex = -1, selectedType = -1;
	selectionChanged(NULL);
	this->repaint();
}

void MapEditor::syncSelectionText()
{
	syncToSelection();
	this->repaint();
}

void MapEditor::addWall()
{
	std::ostringstream oss("");
	oss << "Wall" << totalWall; totalWall++;
	object* newobj= new wall(800, 600, 0);
	objs[++totalIndex] = newobj;
	QListWidgetItem* p = new QListWidgetItem(QString::fromStdString(oss.str()));
	p->setData(1, totalIndex);
	ui.listWidget->addItem(p);
	selectedIndex = totalIndex, selected = newobj, selectedItem = p, selectedType = 1;
	selectionChanged(selectedItem);
	this->repaint();
}

void MapEditor::addRollingWall()
{
	std::ostringstream oss("");
	oss << "RollingWall" << totalWall; totalWall++;
	object* newobj = new rolling_wall(800, 600, 0,0);
	objs[++totalIndex] = newobj;
	QListWidgetItem* p = new QListWidgetItem(QString::fromStdString(oss.str()));
	p->setData(1, totalIndex);
	ui.listWidget->addItem(p);
	selectedIndex = totalIndex, selected = newobj, selectedItem = p, selectedType = 2;
	selectionChanged(selectedItem);
	this->repaint();
}

void MapEditor::addBuff()
{
	std::ostringstream oss("");
	oss << "Buff" << totalWall; totalWall++;
	object* newobj = new buff(800, 600, 0,0);
	objs[++totalIndex] = newobj;
	QListWidgetItem* p = new QListWidgetItem(QString::fromStdString(oss.str()));
	p->setData(1, totalIndex);
	ui.listWidget->addItem(p);
	selectedIndex = totalIndex, selected = newobj, selectedItem = p, selectedType = 3;
	selectionChanged(selectedItem);
	this->repaint();
}

void MapEditor::addSpawn()
{
	std::ostringstream oss("");
	oss << "TankSpawn" << totalWall; totalWall++;
	object* newobj = new tank(800, 600, 0, 1, 0, 0, 0, 0, 0, "Spawn");
	objs[++totalIndex] = newobj;
	QListWidgetItem* p = new QListWidgetItem(QString::fromStdString(oss.str()));
	p->setData(1, totalIndex);
	ui.listWidget->addItem(p);
	selectedIndex = totalIndex, selected = newobj, selectedItem = p, selectedType = 4;
	selectionChanged(selectedItem);
	this->repaint();
}