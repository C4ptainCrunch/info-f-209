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
    QMessageBox::critical(handler->getWindow(), "Erreur", "Le serveur s'est déconnecté");
    QApplication::quit();
    return 0;
}

int main(int argc, char * argv[]) {
    const char * slash = strrchr(argv[0], '/');
    if (slash) {
        std::string clientdir(argv[0], slash - argv[0]);
        chdir(clientdir.c_str());
        #ifdef __APPLE__
        chdir("../../../");
        #endif
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

    window->show();
    if (!handler.connect_socket()) {
        QMessageBox::critical(window, "Erreur", "Impossible de se connecter au serveur");
        QApplication::quit();
        return -1;
    }

    Thread loopThread = Thread(start_loop, (void *)&handler);

    return app.exec();
}
