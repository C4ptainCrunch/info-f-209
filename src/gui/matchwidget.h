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

enum { WIDTH = 30, LENGHT = 60};

class MainWindow;

class MatchWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MatchWidget(QWidget *parent = 0);
    ~MatchWidget();

signals:

public slots:

private:
    MainWindow* parent_;
    QFrame* fieldWidget;

};

#include <mainwindow.h>

#endif // MATCHWIDGET_H
