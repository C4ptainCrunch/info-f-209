#ifndef TEAMHANDLINGWIDGET_H
#define TEAMHANDLINGWIDGET_H

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
#include <../../common/models/NonFieldPlayer.h>
#include <../send-views/views.h>


class MainWindow;


class TeamHandlingWidget: public QWidget {
    Q_OBJECT
public:
    explicit TeamHandlingWidget(MainWindow * parent=0);

signals:

public slots:
    void backToMenu();

private:
    MainWindow * parent_;
};

#include <mainwindow.h>

#endif // TEAMHANDLINGWIDGET_H
