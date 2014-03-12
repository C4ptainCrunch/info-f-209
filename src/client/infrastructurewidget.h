#ifndef INFRASTRUCTUREWIDGET_H
#define INFRASTRUCTUREWIDGET_H

#include <QWidget>
#include <QLabel>

class MainWindow;

class InfrastructureWidget : public QWidget
{
    Q_OBJECT
public:
    explicit InfrastructureWidget(MainWindow *parent = 0);

signals:

public slots:
    void setTrainingField();
    void setField();
    void setInfirmary();
    void setFanShop();
    void setCandyShop();
    void backToMenu();

private:
    MainWindow* parent_;
    QWidget * mainWidget;
    QWidget * currentInfrastructureWidget;
    QLabel * currentInfrastructure;

};

#include <mainwindow.h>

#endif // INFRASTRUCTUREWIDGET_H
