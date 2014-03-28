#ifndef MENUWINDOW_H
#define MENUWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QMessageBox>
#include <QLabel>
#include <QFile>
#include <QPushButton>
#include <QHBoxLayout>
#include <QWidget>
#include <QString>
#include <string>
#include <vector>
#include <QComboBox>
#include <iostream>

#include "../../common/models/Match.h"

class MainWindow;


class MenuWindow: public QWidget {
    Q_OBJECT
public:
    explicit MenuWindow(MainWindow * parent=0);

    QGridLayout * mainLayout;
    QGridLayout * matchLauncherLayout;

    QWidget * quitWidget;
    QWidget * matchLauncherWidget;

    QComboBox * list;

    QPushButton * disconnectButton;
    QPushButton * infrastructureButton;
    QPushButton * auctionHouseButton;
    QPushButton * teamHandlingButton;
    bool isActive();
    void enable();
    void disable();

signals:

public slots:
    void refreshConnectedList(std::vector<std::string> * connectedList);
    void logOut();
    void startMatch(Match * startingMatch);
    void handlePlayers();
    void auctionHouse();
    void infrastructures();
    void askConnectedListRefresh();
    void sendChallenge();

private:
    MainWindow * parent_;
    bool active;

};

#include <mainwindow.h>

#endif // MENUWINDOW_H
