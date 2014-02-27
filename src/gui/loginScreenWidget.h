#ifndef PASSWORDCHECKER_H
#define PASSWORDCHECKER_H

#include <QObject>
#include <QMainWindow>
#include <QLineEdit>

class loginScreenWidget: public QWidget
{
Q_OBJECT
public:
    explicit loginScreenWidget(QWidget *parent = 0);
    void setLineEdit(QLineEdit *username,QLineEdit* password);

signals:

public slots:
    void checkIdPresence();
private:
    QLineEdit* usernameLine;
    QLineEdit* passLine;

};

#endif // PASSWORDCHECKER_H
