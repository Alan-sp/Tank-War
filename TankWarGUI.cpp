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
	statics st;

	QPainterPath qpa;
	qpa.addRect(0, 0, 1000, 1000);
	painter.fillPath(qpa,Qt::black);
	//printf("%d", n);
	for (int i = 0; i < n; i++) {
		QTransform trans;
		trans.rotate(objs[i].getDirection());
		QPixmap pic = st.image_resourse.getImage(objs[i].getState()).transformed(trans);
		painter.drawPixmap(objs[i].getX(), objs[i].getY(), pic.width(), pic.height(), pic);
	}
}

void TankWarGUI::paint_objects(object aobjs[],int an) {//paint all objects in objs
	n = an;
	for (int i = 0; i < n; i++)
		objs[i] = aobjs[i];
	this->repaint();
}