#include "hexagon.h"

Hexagon::Hexagon(int x, int y,QWidget* parent):
    QWidget(parent),x_(x),y_(y), corners()
{
    setCorners();

}
Hexagon::Hexagon(QWidget* parent): QWidget(parent),x_(0),y_(0), corners(){}


Hexagon::~Hexagon(){}

void Hexagon::setX(int x){
    x_ = x;
}

void Hexagon::setY(int y){
    y_ = y;
}

void Hexagon::setCorners(){
    double r = 10;
    const double pi = 2*acos(0.0);
    corners.push_back(QPoint(r*cos(pi/6.0)+x_, r/2.0 + y_));
    corners.push_back(QPoint(x_, y_+r));
    corners.push_back(QPoint(-r*cos(pi/6.0)+x_,y_+r/2.0));
    corners.push_back(QPoint(-r*cos(pi/6.0)+x_,y_-r/2.0));
    corners.push_back(QPoint(x_,y_-r));
    corners.push_back(QPoint(r*cos(pi/6.0)+x_, y_-r/2.0));
    hexagon_ = QPolygon(corners);
}
