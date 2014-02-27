#include "mainwindow.h"
#include <iostream>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent)
{
    this->setWindowTitle("Quidditch Manager 2014");
    //----------------BACKGROUND SETTINGS------------------
    QVBoxLayout *layout = new QVBoxLayout;
    QLabel * image = new QLabel(this);
    image->setPixmap(QPixmap("/home/supayrponey/Documents/Tests/QtTest/mainWindow/loginScreen2.png"));
    layout->addWidget(image);
    this->setLayout(layout);

    //----------------SIZE SETTINGS-----------------------
    this->setFixedHeight(720);
    this->setFixedWidth(1280);

    QFile File("/home/supayrponey/Documents/Tests/QtTest/mainWindow/stylesheet.qss");
    File.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(File.readAll());

    this->setStyleSheet(styleSheet);

    loginScreenWidget* fields = new loginScreenWidget(this);
    QVBoxLayout* fieldsLayout = new QVBoxLayout;
    fields->setFixedHeight(250);
    fields->setFixedWidth(150);
    QLineEdit* userLine_= new QLineEdit("username",fields);

    QLineEdit* passLine_= new QLineEdit("password",fields);
    passLine_->setEchoMode(QLineEdit::Password);

    fields->setLineEdit(userLine_,passLine_);

    QPushButton *connectButton = new QPushButton("Connect",fields);
    QObject::connect(connectButton, SIGNAL(clicked()), fields, SLOT(checkIdPresence()));

    QPushButton *registerButton = new QPushButton("Register",fields);

    QPushButton *quitButton = new QPushButton("Quit",fields);
    QObject::connect(quitButton, SIGNAL(clicked()), this, SLOT(close()));

    fieldsLayout->addWidget(userLine_);
    fieldsLayout->addWidget(passLine_);
    fieldsLayout->addWidget(connectButton);
    fieldsLayout->addWidget(registerButton);
    fieldsLayout->addWidget(quitButton);

    fields->setLayout(fieldsLayout);
    fields->move(this->size().width()/2-75,this->size().height()/2);

}


MainWindow::~MainWindow()
{
}
