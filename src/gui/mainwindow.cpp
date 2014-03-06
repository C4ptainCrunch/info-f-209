﻿#include "mainwindow.h"
#include <iostream>

using namespace std;

MainWindow::MainWindow(QWidget * parent):
    QWidget(parent) {
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


}

MainWindow::~MainWindow()
{}

void MainWindow::setNextScreen(int nextState) {

    switch (nextState) {
        case LOGINMENUSTATE: {
            loginScreenWidget * login = new loginScreenWidget(this);
            login->show();
            break;
        }
        case MAINMENUSTATE: {
            MenuWindow * menu = new MenuWindow(this);
            menu->show();
            break;

        }
        case AUCTIONHOUSESTATE:
            break;
        case TEAMHANDLINGSTATE:
            break;
        case MATCHSTATE:
            break;
    }

}

void QWidget::closeEvent(QCloseEvent * event) {
    if (QMessageBox::question(this, tr("Déconnexion"), tr("Voulez-vous vraiment vous Quitter?"), QMessageBox::Yes | QMessageBox::Cancel, QMessageBox::Yes) == QMessageBox::Yes) {
        event->accept();
    }
    else {
        event->ignore();
    }

}
