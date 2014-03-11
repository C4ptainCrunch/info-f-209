#ifndef TEAMHANDLINGMENU_H
#define TEAMHANDLINGMENU_H

#include <QMainWindow>
#include <QLineEdit>
#include <QMessageBox>
#include <QLabel>
#include <QFile>
#include <QPushButton>
#include <QBoxLayout>
#include <QWidget>
#include <QString>
#include <QComboBox>
#include <QTableWidget>
#include <iostream>

class MainWindow;


class TeamHandlingMenu : public QWidget
{
    Q_OBJECT
public:
    explicit TeamHandlingMenu(MainWindow *parent = 0);

signals:

public slots:
    void backToMenu();

private:
    MainWindow * parent_;
};

#include <mainwindow.h>

#endif // TEAMHANDLINGMENU_H
