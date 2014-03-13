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
#include <vector>
#include <menuwindow.h>
#include <loginscreenwidget.h>
#include <matchwidget.h>
#include <teamhandlingwidget.h>
#include <auctionhousewidget.h>
#include <infrastructurewidget.h>
#include <../../common/models/Case.h>

enum {LOGINMENUSTATE = 1, MAINMENUSTATE = 2, AUCTIONHOUSESTATE = 3, TEAMHANDLINGSTATE = 4, MATCHSTATE = 5, INFRASTRUCTURESTATE = 6};


class MainWindow: public QWidget {
    Q_OBJECT

public:

    explicit MainWindow(QWidget * parent=0);
    QVBoxLayout * backgroundLayout;
    QWidget* getCurrentWidget();
    ~MainWindow();
    void setSocket(Socket* s);
    Socket* getSocket();

signals:
    void loginSuccess();
    void loginFailure(int);
    void registerSuccess();
    void userList(vector<string>);
    void registerFailure(int);
    void newDefi(std::string username);
    void refreshField(Case grid_[WIDTH][LENGTH]);

public slots:
    void setNextScreen(int nextState);
    void getDefi(std::string username);


private:
    QLineEdit * usernameLine;
    QLineEdit * passLine;
    QWidget * currentWidget;
    Socket* s_;

};

#endif // MAINWINDOW_H
