#include "TankWarGUI.h"
#include <QtWidgets/QApplication>
#include "statics.h"
#include "ImageResource.h"

int arg0 = 1;
int& arg1 = arg0;
char **arg2;

ImageResource statics::image_resourse;
QApplication statics::qapp(arg1,arg2);
TankWarGUI statics::gui;
int main()
{
    statics st;
    st.gui.show();

    return st.qapp.exec();
}
