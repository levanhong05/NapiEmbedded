#include "napilcddisplay.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    NapiLCDDisplay w;
    w.showMaximized();

    return a.exec();
}
