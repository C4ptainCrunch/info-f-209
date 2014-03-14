#include "mainwindow.h"
#include <iostream>

using namespace std;

MainWindow::MainWindow(QWidget * parent):
    QWidget(parent) {
    s_ = 0;
    cout << QCoreApplication::applicationDirPath().toStdString() << endl;

    //----------------TITLE SETTINGS-----------------------
    this->setWindowTitle("Quidditch Manager 2014");

    //-----------------SIZE SETTINGS-----------------------
    this->setFixedHeight(720);
    this->setFixedWidth(1280);

    //----------------STYLE SETTINGS-----------------------
    QFile File(QCoreApplication::applicationDirPath() + "/stylesheets/stylesheet.qss");
    File.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(File.readAll());

    this->setStyleSheet(styleSheet);

    //-----------------LOGIN SCREEN-----------------------
    loginScreenWidget * login = new loginScreenWidget(this);
    login->show();

    //-----------------SIGNAUX----------------------------
    QObject::connect(this, SIGNAL(newDefi(std::string)), this, SLOT(getDefi(std::string)));


}

MainWindow::~MainWindow()
{}

void MainWindow::setNextScreen(int nextState) {
    cout << nextState;
    switch (nextState) {
        case LOGINMENUSTATE: {
            loginScreenWidget * login = new loginScreenWidget(this);
            currentWidget = login;
            login->show();
            break;
        }
        case MAINMENUSTATE: {
            MenuWindow * menu = new MenuWindow(this);
            currentWidget = menu;
            menu->show();
            menu->enable();
            break;

        }
        case AUCTIONHOUSESTATE: {
            AuctionHouseWidget * auctionHouse = new AuctionHouseWidget(this);
            currentWidget = auctionHouse;
            auctionHouse->show();
            break;
        }
        case TEAMHANDLINGSTATE: {
            TeamHandlingWidget * teamHandling = new TeamHandlingWidget(this);
            currentWidget = teamHandling;
            teamHandling->show();
            break;
        }
        case MATCHSTATE: {
            MatchWidget * match = new MatchWidget(this);
            currentWidget = match;
            match->show();
            break;
        }
        case INFRASTRUCTURESTATE: {
            InfrastructureWidget * infrastructure = new InfrastructureWidget(this);
            currentWidget = infrastructure;
            infrastructure->show();
            break;

        }
    }

}

QWidget * MainWindow::getCurrentWidget() {
    return currentWidget;
}


void QWidget::closeEvent(QCloseEvent * event) {
    event->accept();
    /*
     * TODO

       if(QMessageBox::question(this,tr("Déconnexion"),tr("Voulez-vous vraiment vous Quitter?"),QMessageBox::Yes |QMessageBox::Cancel,QMessageBox::Yes ) == QMessageBox::Yes){
        event->accept();
       }
       else{
        event->ignore();
       }
     */
}

void MainWindow::getDefi(string username) {
    int accept = QMessageBox::question(this, "Défi", QString::fromStdString(username) + " vous défie.\nAcceptez-vous le défi?", QMessageBox::Yes | QMessageBox::No);
    if (accept == QMessageBox::Yes) {
        //TODO lanch match
    }
    else if (accept == QMessageBox::No) {
        //TODO say no to server
    }
}

void MainWindow::setSocket(Socket * s) {
    s_ = s;
}

Socket * MainWindow::getSocket() {
    return s_;
}
