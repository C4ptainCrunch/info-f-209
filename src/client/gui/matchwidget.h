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
#include "../../common/lib/socket/Socket.h"

enum { WIDTH = 30, LENGHT = 64};

class MainWindow;

class MatchWidget: public QWidget {
    Q_OBJECT
public:
    explicit MatchWidget(QWidget * parent=0);
    void mousePressEvent(QMouseEvent *);
    void generateGrid() ;
    void refreshField();
    ~MatchWidget();

signals:

public slots:

private:
    MainWindow * parent_;
    QWidget * mainWidget;
    QLabel * ownScore;
    QLabel * opponentScore;
    QFrame * fieldWidget;
    int grid_[WIDTH][LENGHT];

};

#include <mainwindow.h>

#endif // MATCHWIDGET_H
