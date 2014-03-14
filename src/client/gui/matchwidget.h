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
#include <../../common/models/Case.h>
#include "../../common/lib/socket/Socket.h"


class MainWindow;

class MatchWidget: public QWidget {
    Q_OBJECT
public:
    explicit MatchWidget(QWidget * parent=0);
    void mousePressEvent(QMouseEvent *);
    void generateGrid() ;
    ~MatchWidget();

signals:

public slots:
    void refreshField(Case grid[WIDTH][LENGTH]);

private:
    MainWindow * parent_;
    QWidget * mainWidget;
    QLabel * ownScore;
    QLabel * opponentScore;
    QFrame * fieldWidget;
    int grid_[WIDTH][LENGTH];

};

#include <mainwindow.h>

#endif // MATCHWIDGET_H
