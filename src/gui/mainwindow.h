#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QMessageBox>
#include <QLabel>
#include <QFile>
#include <QPushButton>
#include <QVBoxLayout>
#include <QCloseEvent>
#include <QCoreApplication>
#include <menuwindow.h>
#include <loginscreenwidget.h>

enum {LOGINMENUSTATE = 1, MAINMENUSTATE = 2, AUCTIONHOUSESTATE = 3, TEAMHANDLINGSTATE = 4,MATCHSTATE = 5};

class MainWindow : public QWidget
{
    Q_OBJECT

public:

    explicit MainWindow(QWidget *parent = 0);
    QVBoxLayout *backgroundLayout;
    ~MainWindow();

public slots:
    void setNextScreen(int nextState);

private:
    QLineEdit* usernameLine;
    QLineEdit* passLine;
    //QVector<QWidget*> currentWidgets;

};

#endif // MAINWINDOW_H
