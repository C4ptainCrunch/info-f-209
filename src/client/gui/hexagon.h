#ifndef HEXAGON_H
#define HEXAGON_H

#include <QWidget>
#include <QDesktopWidget>
#include <QPolygon>
#include <QPoint>
#include <QPainter>
#include <QVector>
#include <QFrame>
#include <cmath>
#include <iostream>

using namespace std;

class Hexagon: public QWidget {
    Q_OBJECT
public:
    explicit Hexagon(int x, int y, QWidget * parent=0);
    explicit Hexagon(QWidget * parent=0);
    ~Hexagon();
    void setCorners();
    void setX(int x);
    void setY(int y);
    QPolygon hexagon_;

protected:

private:
    int x_;
    int y_;
    QVector<QPoint> corners;

};


#endif
