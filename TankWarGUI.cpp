#include "TankWarGUI.h"
#include "qpainter.h"
#include "object.cpp"
#include "statics.h"
#include "qpainterpath.h"
#include "qtransform.h"

TankWarGUI::TankWarGUI(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    n = 0;
}

TankWarGUI::~TankWarGUI()
{}

void TankWarGUI::paintEvent(QPaintEvent* event) {
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing, true);
	statics st;

	QPainterPath qpa;
	qpa.addRect(0, 0, 1200, 800);
	painter.fillPath(qpa, Qt::black);
	for (int i = 0; i < n; i++) {
		QTransform trans;
		trans.rotate(objs[i].getDirection() % 360, Qt::ZAxis);
		QPixmap pic = st.image_resourse.getImage(objs[i].getState()).transformed(trans);
		painter.drawPixmap(objs[i].getX()-pic.width()/2, objs[i].getY()-pic.height()/2, pic.width(), pic.height(), pic);
	}
}

void TankWarGUI::paint_objects(object aobjs[],int an) {//paint all objects in objs
	n = an;
	for (int i = 0; i < n; i++)
		objs[i] = aobjs[i];
	emit repaint_signal();
}

void TankWarGUI::repaint_slot() {
	this->repaint();
}