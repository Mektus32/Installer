#include "mainwindow.hpp"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, nullptr);
    MainWindow w;
    w.setFixedSize(402, 369);
    w.show();
    return a.exec();
}
