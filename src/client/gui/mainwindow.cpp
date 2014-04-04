#include "mainwindow.h"
#include <iostream>

using namespace std;

MainWindow::MainWindow(QWidget * parent):
    QWidget(parent) {
    s_ = 0;
    menu_ = NULL;
    match_ = NULL;
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

    //-----------------------CUSTOM SIGNALS CONNECTION--------------------
    QObject::connect(this, SIGNAL(newDefi(std::string *,int)), this, SLOT(getDefi(std::string *,int)));

    QObject::connect(this, SIGNAL(playerList(std::vector<NonFieldPlayer *> *)), this, SLOT(recievePlayers(std::vector<NonFieldPlayer *> *)));


}

MainWindow::~MainWindow()
{}

void MainWindow::setNextScreen(int nextState, Match * startingMatch, bool isGuest, int matchID) {
    switch (nextState) {
        case LOGINMENUSTATE: {
            loginScreenWidget * login = new loginScreenWidget(this);
            currentWidget = login;
            login->show();
            break;
        }
        case MAINMENUSTATE: {
            if (menu_ != NULL){
                delete menu_;
                menu_ = NULL;
            }
            menu_ = new MenuWindow(this);
            //currentWidget = menu;
            menu_->show();
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
            if (match_ != NULL){
                delete match_;
                match_ = NULL;
            }
            match_ = new MatchWidget(startingMatch, isGuest, matchID, this);
            //currentWidget = match;
            //match->show();
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
    if (QMessageBox::question(this, tr("Déconnexion"), tr("Voulez-vous vraiment vous Quitter?"), QMessageBox::Yes | QMessageBox::Cancel, QMessageBox::Yes) == QMessageBox::Yes) {
        event->accept();
    }
    else {
        event->ignore();
    }
}

void MainWindow::askPlayers() {
    sviews::playerlist(this->getSocket());
}

void MainWindow::recievePlayers(std::vector<NonFieldPlayer *> * players) {
    playersList = *players;
    this->setNextScreen(TEAMHANDLINGSTATE);
}

vector<NonFieldPlayer *> MainWindow::getPlayers() {
    return playersList;
}


void MainWindow::getDefi(string * username, int matchID) {
    int accept = QMessageBox::question(this, "Défi", QString::fromStdString(*username) + " vous défie.\nAcceptez-vous le défi?", QMessageBox::Yes | QMessageBox::No);
    if (accept == QMessageBox::Yes) {
        sviews::acceptChallenge(this->s_, *username, matchID);
    }
    else if (accept == QMessageBox::No) {
        sviews::refuseChallenge(this->s_, *username, matchID);
    }
    delete username;
    username = NULL;
}

void MainWindow::setSocket(Socket * s) {
    s_ = s;
}

Socket * MainWindow::getSocket() {
    return s_;
}

bool MainWindow::isFirstMenu(){
    return firstMenu;
}

void MainWindow::setFirstMenu(bool menu){
    firstMenu = menu;
}
