#include "menuwindow.h"
#include <iostream>
using namespace std;

MenuWindow::MenuWindow(MainWindow * parent):
    QWidget(parent), parent_(parent) {
    bool firstMenu = parent_->isFirstMenu();
    parent_->setFirstMenu(false);
    cout<<"PREMIER MENU : "<<firstMenu;
    //-------------------------SIZE SETTINGS---------------------------
    this->setFixedHeight(720);
    this->setFixedWidth(1280);

    //----------------------BACKGROUND SETTINGS---------------------------
    QVBoxLayout * layout = new QVBoxLayout;
    QLabel * image = new QLabel(this);
    image->setPixmap(QPixmap(QCoreApplication::applicationDirPath() + "/images/Quidditch_pitch_hogwarts.jpg"));
    layout->addWidget(image);
    this->setLayout(layout);

    //---------------------MAIN CONTAINER WIDGET---------------------------
    QWidget * mainWidget = new QWidget(this);
    mainWidget->setFixedHeight(720);
    mainWidget->setFixedWidth(1280);
    QGridLayout * mainLayout = new QGridLayout(mainWidget);

    matchLauncherWidget  = new QWidget(this);

    matchLauncherLayout = new QGridLayout(matchLauncherWidget);

    //---------------------------OPPONENT CHOICE-------------------
    list = new QComboBox(matchLauncherWidget);
    //this->askConnectedListRefresh();

    QPushButton * startMatchButton = new QPushButton("DEFIER", matchLauncherWidget);

    startMatchButton->setMinimumHeight(40);
    startMatchButton->setStyleSheet(" font-weight: bold; font-size: 18pt;");
    QPushButton * refreshButton = new QPushButton("Rafraichir", matchLauncherWidget);
    //if(firstMenu){
        QObject::disconnect(refreshButton,0,0,0);
    //}
    QObject::connect(refreshButton, SIGNAL(clicked()), this, SLOT(askConnectedListRefresh()));

    matchLauncherLayout->addWidget(list, 0, 0, 1, 3);
    matchLauncherLayout->addWidget(startMatchButton, 1, 0, 1, 4);
    matchLauncherLayout->addWidget(refreshButton, 0, 3);


    matchLauncherWidget->setFixedHeight(100);
    matchLauncherWidget->setFixedWidth(400);


    matchLauncherWidget->setLayout(matchLauncherLayout);

    //--------------------CHALLENGE BUTTON--------------------------
    //if(firstMenu){
        QObject::disconnect(startMatchButton,0,0,0);
    //}
    QObject::connect(startMatchButton, SIGNAL(clicked()), this, SLOT(sendChallenge()));

    //-------------------AUCTIONHOUSE BUTTON-------------------------
    auctionHouseButton = new QPushButton("Encheres");
    auctionHouseButton->setMinimumHeight(60);
    //if(firstMenu){
        QObject::disconnect(auctionHouseButton,0,0,0);
        connect(auctionHouseButton, SIGNAL(clicked()), this, SLOT(auctionHouse()));
    //}

    //-----------------TEAM HANDLING BUTTON--------------------------
    teamHandlingButton = new QPushButton("Gestion de Team");
    teamHandlingButton->setMinimumHeight(60);
    //if(!firstMenu){
    QObject::disconnect(teamHandlingButton,0,0,0);

    connect(teamHandlingButton, SIGNAL(clicked()), this, SLOT(handlePlayers()));

    //-----------------INFRASTRUCTURE BUTTON--------------------------
    infrastructureButton = new QPushButton("Infrastructures");
    infrastructureButton->setMinimumHeight(60);
    //if(firstMenu){

        QObject::disconnect(infrastructureButton,0,0,0);
        connect(infrastructureButton, SIGNAL(clicked()), this, SLOT(infrastructures()));
    //}

    //------------------DISCONNECT BUTTON---------------------------
    disconnectButton = new QPushButton("Quitter");
    disconnectButton->setMinimumHeight(60);
    //if(firstMenu){

        QObject::disconnect(disconnectButton,0,0,0);
        connect(disconnectButton, SIGNAL(clicked()), this, SLOT(logOut()));
    //}

    //-----------------------CUSTOM SIGNALS CONNECTION--------------------

    //if(firstMenu){
        QObject::disconnect(parent_, SIGNAL(startMatch(Match *,bool,int)),0,0);
        //QObject::disconnect(0,0,this,SLOT(refreshConnectedList(std::vector<std::string> *)));
        QObject::connect(parent_, SIGNAL(startMatch(Match *,bool,int)), this, SLOT(startMatch(Match *,bool,int)));
        QObject::connect(parent_, SIGNAL(userList(std::vector<std::string> *)), this, SLOT(refreshConnectedList(std::vector<std::string> *)));
    //}
    //----------------USELESS WIDGETS FOR A BETTER GUI---------------
    QWidget * temp = new QWidget;
    temp->setFixedHeight(20);
    temp->setFixedWidth(20);
    QWidget * temp2 = new QWidget;
    temp2->setFixedHeight(20);
    temp2->setFixedWidth(20);

    //---------------------ADD WIDGETS TO THE WINDOW--------------
    mainLayout->addWidget(temp, 0, 0, 1, 1);
    mainLayout->addWidget(auctionHouseButton, 1, 1, 1, 1);
    mainLayout->addWidget(disconnectButton, 4, 2, 1, 1);
    mainLayout->addWidget(teamHandlingButton, 1, 3, 1, 1);
    mainLayout->addWidget(infrastructureButton, 1, 2, 1, 1);
    mainLayout->addWidget(matchLauncherWidget, 2, 2, 2, 1);
    mainLayout->addWidget(temp2, 5, 4, 1, 1);
    mainWidget->setLayout(mainLayout);
    //--------------------------DISPLAY---------------------------
    mainWidget->show();


}

void MenuWindow::handlePlayers() {
    parent_->askPlayers();

}

bool MenuWindow::isActive() {
    return active;
}

void MenuWindow::enable() {
    active = true;
}
void MenuWindow::disable() {
    active = false;
}


void MenuWindow::infrastructures() {
    parent_->setNextScreen(INFRASTRUCTURESTATE);

}

void MenuWindow::sendChallenge() {
     string opponent = list->currentText().toStdString();
     sviews::challenge(parent_->getSocket(), opponent);

}

void MenuWindow::startMatch(Match * startingMatch, bool isGuest, int matchID) {
    parent_->setNextScreen(MATCHSTATE, startingMatch, isGuest, matchID);
}

void MenuWindow::logOut() {
    parent_->close();


}

void MenuWindow::auctionHouse() {
    parent_->setNextScreen(AUCTIONHOUSESTATE);
}

void MenuWindow::refreshConnectedList(vector<string> * connectedList) {
    cout << "JE RECOIS LA LISTE DES CONNECTES" << endl;
    list->clear();
    list->addItem("Choisissez un adversaire");
    list->insertSeparator(1);


    for (int i = 0; i < (int)connectedList->size(); ++i) {
        cout << "refreshConnectedList i :" << i << endl;
        string mess = (*connectedList)[i];
        cout << "list: " << mess << endl;
        list->addItem(QString::fromStdString(mess));
    }

    delete connectedList;
    connectedList = NULL;
    cout<<"C'EST RAFRAICHI"<<endl;
}

void MenuWindow::askConnectedListRefresh() {
    cout << "JE DEMANDE LA LISTE DES CONNECTES" << endl;
    sviews::userlist(parent_->getSocket());
    cout<<"C'EST DEMANDE"<<endl;
}
