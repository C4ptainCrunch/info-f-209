#include "mainwindow.h"
#include <QApplication>
#include <QPushButton>
#include <QGraphicsView>
#include <QGridLayout>
#include <QLabel>
#include <iostream>
#include <menuwindow.h>
using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow* window = new MainWindow();
    MenuWindow* menuWindow = new MenuWindow();
    //menuWindow->show();

    window->show();

    return a.exec();
}
