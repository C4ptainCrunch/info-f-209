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
#include <../send-views/views.h>


enum {LOGINMENUSTATE = 1, MAINMENUSTATE = 2, AUCTIONHOUSESTATE = 3, TEAMHANDLINGSTATE = 4, MATCHSTATE = 5, INFRASTRUCTURESTATE = 6};


class MainWindow: public QWidget {
    Q_OBJECT

public:

    explicit MainWindow(QWidget * parent=0);
    QVBoxLayout * backgroundLayout;
    QWidget * getCurrentWidget();
    ~MainWindow();
    void setSocket(Socket * s);
    Socket * getSocket();
    void askPlayers();
    vector<NonFieldPlayer *> getPlayers();

signals:
    void loginSuccess();
    void loginFailure(int);
    void registerSuccess();
    void userList(std::vector<std::string> *);
    void registerFailure(int);
    void newDefi(std::string * username, int matchID);
    void setMatch(Match * match);
    void endMatch(int signal);
    void startMatch(Match * match, bool isGuest,int matchID);
    void updateMatch(Match * match);

    void playerList(std::vector<NonFieldPlayer *> * players);

public slots:
    void setNextScreen(int nextState, Match * startingMatch=0, bool isGuest = false, int matchID = -1);
    void getDefi(std::string * username, int matchID);
    void recievePlayers(std::vector<NonFieldPlayer *> * players);


private:
    QLineEdit * usernameLine;
    QLineEdit * passLine;
    QWidget * currentWidget;
    Socket * s_;
    std::vector<NonFieldPlayer *> playersList;

};

#endif // MAINWINDOW_H
