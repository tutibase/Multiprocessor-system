#include "MainWindow/mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    Processor tmp_p(0);
    tmp_p.writeLine(0);

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
