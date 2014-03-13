#include "mainwindow.h"
#include <QApplication>
#include <QPushButton>
#include <QGraphicsView>
#include <QGridLayout>
#include <QLabel>
#include <QPixmap>
#include <iostream>
#include <menuwindow.h>
#include "../receive-views/serverhandler.h"
using namespace std;

int main(int argc, char * argv[]) {
    QApplication a(argc, argv);

    MainWindow * window = new MainWindow();
    //MenuWindow * menuWindow = new MenuWindow();
    //menuWindow->show();

    window->show();
    ServerHandler k = ServerHandler("bill.local", 5000, window);
    k.connect_socket();
    k.loop();
    return a.exec();
}
