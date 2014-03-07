#include "menuwindow.h"
#include <iostream>
using namespace std;

MenuWindow::MenuWindow(MainWindow * parent):
    QWidget(parent), parent_(parent) {
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
    QVector<QString> connectedList;
    connectedList.push_back("Romain");
    connectedList.push_back("Nikita");
    connectedList.push_back("Bruno");
    list = new QComboBox(matchLauncherWidget);
    list->addItem("Choisissez un adversaire");
    list->insertSeparator(1);

    for (int i = 0; i < connectedList.size(); ++i) {
        list->addItem(QString(connectedList[i]));
    }
    QPushButton * startMatchButton = new QPushButton("DEFIER", matchLauncherWidget);
    QObject::connect(startMatchButton, SIGNAL(clicked()), this, SLOT(startMatch()));
    startMatchButton->setMinimumHeight(40);
    startMatchButton->setStyleSheet(" font-weight: bold; font-size: 18pt;");
    QPushButton * refreshButton = new QPushButton("Rafraichir", matchLauncherWidget);
    QObject::connect(refreshButton, SIGNAL(clicked()), this, SLOT(refreshConnectedList()));

    matchLauncherLayout->addWidget(list, 0, 0, 1, 3);
    matchLauncherLayout->addWidget(startMatchButton, 1, 0, 1, 4);
    matchLauncherLayout->addWidget(refreshButton, 0, 3);


    matchLauncherWidget->setFixedHeight(100);
    matchLauncherWidget->setFixedWidth(400);


    matchLauncherWidget->setLayout(matchLauncherLayout);

    //-------------------AUCTIONHOUSE BUTTON-------------------------
    auctionHouseButton = new QPushButton("Encheres");
    auctionHouseButton->setMinimumHeight(60);

    //-----------------TEAM HANDLING BUTTON--------------------------
    teamHandlingButton = new QPushButton("Gestion de Team");
    teamHandlingButton->setMinimumHeight(60);

    //------------------DISCONNECT BUTTON---------------------------
    disconnectButton = new QPushButton("Se deconnecter");
    disconnectButton->setMinimumHeight(60);
    connect(disconnectButton, SIGNAL(clicked()), this, SLOT(logOut()));

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
    //mainLayout->addWidget(quitWidget,4,3,1,1);
    mainLayout->addWidget(matchLauncherWidget, 2, 2, 2, 1);
    mainLayout->addWidget(temp2, 5, 4, 1, 1);
    mainWidget->setLayout(mainLayout);
    //--------------------------DISPLAY---------------------------
    mainWidget->show();


}

void MenuWindow::startMatch() {
    parent_->setNextScreen(MATCHSTATE);
}

void MenuWindow::logOut() {
    //TODO : DISCONNECT CLIENT FROM SERVER
    if (QMessageBox::question(this, tr("Déconnexion"), tr("Voulez-vous vraiment vous déconnecter?"), QMessageBox::Yes | QMessageBox::Cancel, QMessageBox::Yes) == QMessageBox::Yes) {
        parent_->setNextScreen(LOGINMENUSTATE);
    }

}

void MenuWindow::refreshConnectedList() {
    list->clear();
    QVector<QString> connectedList;
    connectedList.push_back("Am");
    connectedList.push_back("Stram");
    connectedList.push_back("Gram");
    list->addItem("Choisissez un adversaire");
    list->insertSeparator(1);


    for (int i = 0; i < connectedList.size(); ++i) {
        list->addItem(QString(connectedList[i]));
    }


}
