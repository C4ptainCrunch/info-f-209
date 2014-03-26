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
    explicit MatchWidget(QWidget * parent=0);
    void mousePressEvent(QMouseEvent *);
    void generateGrid();
    ~MatchWidget();
    void askMatchToServer();
    void refreshField(Case grid[WIDTH][LENGTH], Position highlightedCase = Position());
signals:

public slots:
    void setMatch(Match*);

private:
    MainWindow * parent_;
    QWidget * mainWidget;
    QLabel * ownScore;
    QLabel * opponentScore;
    QFrame * fieldWidget;
    Match* currentMatch;
    Case grid[WIDTH][LENGTH];

};

#include <mainwindow.h>

#endif // MATCHWIDGET_H
