#ifndef MATCHWIDGET_H
#define MATCHWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QCoreApplication>
#include <QGridLayout>
#include <QPushButton>
#include <QTextEdit>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QFrame>
#include <QTextEdit>
#include <cmath>

#include <iostream>

#include "hexagon.h"
#include "../../common/models/Case.h"
#include "../../common/lib/socket/Socket.h"
#include "../../common/models/Match.h"


class MainWindow;

class MatchWidget: public QWidget {
    Q_OBJECT
public:
    explicit MatchWidget(Match *startingMatch,QWidget * parent=0);
    void mousePressEvent(QMouseEvent *);
    void generateGrid();
    ~MatchWidget();
    void askMatchToServer();
    void refreshField();
    Position getCase(QMouseEvent * event);
    bool isCaseHighlighted(unsigned i, unsigned j);
signals:

public slots:
    void setCurrentMatch(Match*);
    void nextPlayer();
    void endTurn();

private:
    MainWindow * parent_;
    QWidget * mainWidget;
    QLabel * ownScore;
    QLabel * opponentScore;
    QFrame * fieldWidget;
    Match* currentMatch_;
    Case grid_[WIDTH][LENGTH];
    QLabel* playerLabels_[2][4];
    Way highlightedCases;
    std::vector<Way> chosenWays;
    bool playerSelected = false;

};

#include <mainwindow.h>

#endif // MATCHWIDGET_H
