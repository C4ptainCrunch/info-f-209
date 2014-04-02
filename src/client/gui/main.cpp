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
#include "../../common/lib/thread/thread.h"

using namespace std;

void * start_loop(void * arg) {
    ServerHandler * handler = (ServerHandler *) arg;
    handler->loop();
    perror("string vide");
    cout << errno << endl;
    QMessageBox::critical(handler->getWindow(), "Erreur", "Le serveur s'est déconnecté");
    exit(1);
    return 0;
}

int main(int argc, char * argv[]) {
    const char * slash = strrchr(argv[0], '/');
    if (slash) {
        std::string clientdir(argv[0], slash - argv[0]);
        chdir(clientdir.c_str());
    }

    QApplication app(argc, argv);

    MainWindow * window = new MainWindow();

    string hostname = "localhost";
    int port = 9000;
    if (argc == 2) {
        hostname = argv[1];
    }
    if (argc == 3) {
        port = stoi(argv[2]);
    }
    ServerHandler handler = ServerHandler(hostname, port, window);

    handler.connect_socket();

    window->show();
    emit window->setNextScreen(MAINMENUSTATE);
    Thread loopThread = Thread(start_loop, (void *)&handler);

    return app.exec();
}
