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
#include <QComboBox>
#include <iostream>

class MainWindow;


class MenuWindow : public QWidget
{
    Q_OBJECT
public:
    explicit MenuWindow(MainWindow *parent = 0);

    QGridLayout* mainLayout;
    QGridLayout* matchLauncherLayout;

    QWidget* quitWidget;
    QWidget* matchLauncherWidget;

    QComboBox *list;

    QPushButton* disconnectButton;
    QPushButton* auctionHouseButton;
    QPushButton* teamHandlingButton;

signals:

public slots:
    void refreshConnectedList();
    void logOut();
    void startMatch();

private:
    MainWindow* parent_;

};

#include <mainwindow.h>

#endif // MENUWINDOW_H
