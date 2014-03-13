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

    string hostname = "localhost";
    int port = 500;
    if (argc == 2){
        hostname = argv[1];
    }
    if (argc == 3){
        port = stoi(argv[2]);
    }

    ServerHandler handler = ServerHandler(hostname, port, window);

    handler.connect_socket();

    window->show();

    handler.loop();

    return a.exec();
}
