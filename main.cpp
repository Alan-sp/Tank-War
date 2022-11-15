#include "TankWarGUI.h"
#include <QtWidgets/QApplication>
#include "statics.h"
#include "qthread.h"
#include "ImageResource.h"
#include "MyThread.h"

int arg0 = 1;
int& arg1 = arg0;
char **arg2;

image_resource statics::image_resourse;
QApplication statics::qapp(arg1,arg2);
TankWarGUI statics::gui;
int main()
{
    statics st;
    st.gui.show();
    
    st.image_resourse.add_image_resource(0, "D:/q.jpg");

    QThread thd;
    MyThread mthd;
    mthd.moveToThread(&thd);
    thd.start();

    QObject::connect(&st.gui, SIGNAL(repaint_signal()), &st.gui, SLOT(repaint_slot()));
    QObject::connect(&mthd, SIGNAL(MyThreadTTRan()), &mthd, SLOT(ran()));

    emit mthd.MyThreadTTRan();
    
    st.qapp.exec();

    return 0;
}