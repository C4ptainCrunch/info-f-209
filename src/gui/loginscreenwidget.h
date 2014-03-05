#ifndef LOGINSCREENWIDGET_H
#define LOGINSCREENWIDGET_H

#include <QWidget>
#include <QMainWindow>
#include <QLineEdit>
#include <QMessageBox>
#include <QLabel>
#include <QFile>
#include <QPushButton>
#include <QVBoxLayout>
#include <menuwindow.h>

class MainWindow;

class loginScreenWidget : public QWidget
{
    Q_OBJECT
public:
    explicit loginScreenWidget(MainWindow *parent = 0);

signals:

public slots:
    void checkIdPresence();
    void showCredits();
    void exit();

private:
    QLineEdit* usernameLine;
    QLineEdit* passLine;
    MainWindow* parent_;

};
#include <mainwindow.h>

#endif // LOGINSCREENWIDGET_H
