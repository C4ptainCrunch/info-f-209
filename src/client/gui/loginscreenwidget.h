#ifndef LOGINSCREENWIDGET_H
#define LOGINSCREENWIDGET_H

#include <QWidget>
#include <QMainWindow>
#include <QLineEdit>
#include <QMessageBox>
#include <QLabel>
#include <QFile>
#include <QPushButton>
#include <QVBoxLayout>
#include <QFrame>
#include <menuwindow.h>

#include "../send-views/views.h"

class MainWindow;

class loginScreenWidget: public QWidget {
    Q_OBJECT
public:
    explicit loginScreenWidget(MainWindow * parent=0);
    void enableButtons();
    void disableButtons();

signals:

public slots:
    void logIn();
    void registerUser();
    void showCredits();
    void exit();
    void acceptLogin();
    void refuseLogin(int errorCode);
    void refuseRegister(int errorCode);
    void acceptRegister();

private:
    QLineEdit * usernameLine;
    QPushButton * connectButton;
    QPushButton * creditsButton;
    QPushButton * registerButton;
    QPushButton * quitButton;
    QLineEdit * passLine;
    MainWindow * parent_;

};
#include <mainwindow.h>

#endif // LOGINSCREENWIDGET_H
