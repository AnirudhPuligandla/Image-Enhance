// http://www.amin-ahmadi.com

#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setupMainWindow(w);
    //w.setupMainPage(w);
    w.show();

    return a.exec();
}
