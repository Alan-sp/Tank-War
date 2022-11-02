#include "TankWarGUI.h"
#include <QtWidgets/QApplication>
#include "statics.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    statics st;
    st.gui.show();
    return a.exec();
}
