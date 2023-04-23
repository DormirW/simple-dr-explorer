#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("医用X光透视图像简易浏览器");
    w.show();
    return a.exec();
}
