#include "loginScreenWidget.h"
#include <iostream>
#include <QMessageBox>

using namespace std;

loginScreenWidget::loginScreenWidget(QWidget *parent) :
    QWidget(parent),usernameLine(NULL),passLine(NULL)
{
}
void loginScreenWidget::setLineEdit(QLineEdit *username,QLineEdit* password){
    usernameLine = username;
     passLine = password;
}

void loginScreenWidget::checkIdPresence(){
    QString username = usernameLine->text();
    QString password = passLine->text();
    if((username.isEmpty() && password.isEmpty()) or (username=="username" && password=="password")){
        //QMessageBox* emptyFields;
        QMessageBox::warning(this,"Champs Vides","Vous n'avez pas fourni de nom d'utilisateur et de mot de passe");
        //emptyFields->setStyleSheet("QLineEdit { background-color: white }");
    }
}
