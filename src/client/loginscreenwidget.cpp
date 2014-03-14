#include "loginscreenwidget.h"
#include <iostream>
#include <QCoreApplication>
#include <QFormLayout>
#include <QPalette>
#include <QDialogButtonBox>
using namespace std;

loginScreenWidget::loginScreenWidget(MainWindow * parent):
    QWidget(parent) {
    parent_ = parent;

    //-------------------------BACKGROUND SETTINGS---------------------------
    QVBoxLayout * layout = new QVBoxLayout;
    QLabel * image = new QLabel(this);
    image->setPixmap(QPixmap(QCoreApplication::applicationDirPath() + "/images/loginScreen2.png"));
    layout->addWidget(image);
    this->setLayout(layout);

    //----------------------------SIZE SETTINGS---------------------------
    this->setFixedHeight(720);
    this->setFixedWidth(1280);

    //----------------------------LINE/BUTTONS---------------------------
    QFrame * fields = new QFrame(this);

    QVBoxLayout * fieldsLayout = new QVBoxLayout;
    fields->setFixedHeight(250);
    fields->setFixedWidth(150);
    QLineEdit * userLine_ = new QLineEdit("username", fields);

    QLineEdit * passLine_ = new QLineEdit("password", fields);
    passLine_->setEchoMode(QLineEdit::Password); // Display bullets instead of char

    usernameLine = userLine_;
    passLine = passLine_;

    //-------------------------------BUTTONS---------------------------
    QPushButton * creditsButton = new QPushButton("Credits", fields);
    QObject::connect(creditsButton, SIGNAL(clicked()), this, SLOT(showCredits()));

    QPushButton * connectButton = new QPushButton("Connect", fields);
    QObject::connect(connectButton, SIGNAL(clicked()), this, SLOT(checkIdPresence()));

    QPushButton * registerButton = new QPushButton("Register", fields);
    QObject::connect(registerButton, SIGNAL(clicked()),this, SLOT(registerUser()));

    QPushButton * quitButton = new QPushButton("Quit", fields);
    QObject::connect(quitButton, SIGNAL(clicked()), this, SLOT(exit()));

    //--------------------------ADDS THE WIGETS---------------------------
    fieldsLayout->addWidget(userLine_);
    fieldsLayout->addWidget(passLine_);
    fieldsLayout->addWidget(connectButton);
    fieldsLayout->addWidget(registerButton);
    fieldsLayout->addWidget(creditsButton);
    fieldsLayout->addWidget(quitButton);

    fields->setLayout(fieldsLayout);
    fields->move(this->size().width() / 2 - 75, this->size().height() / 2);
}
void loginScreenWidget::showCredits() {
    QMessageBox::information(this, "Credits",
                             "Application créée par Romain, Nikita et Bruno\nAvec la participation de Tsotne et Cédric\n"
                             "Librairie graphique utilisée : Qt 5.2.1\n"
                             "Background : http://fanzone.potterish.com/wp-content/gallery/video-game-hp6-playstation-3/edp_ps3_screencap_02.jpg\n"
                             "Dans le cadre du cours INFO-F-209");

}


void loginScreenWidget::checkIdPresence() {
    QString username = usernameLine->text();
    QString password = passLine->text();
    if ((username.isEmpty() && password.isEmpty())or((username == "username") && (password == "password"))) {
        QMessageBox::warning(this, "Champs Vides", "Vous n'avez pas fourni de nom d'utilisateur et de mot de passe");
    }
    else {
        //TODO VERIFY ID/PASSWORD

        parent_->setNextScreen(MAINMENUSTATE);
        //else {QMessageBox::warning(this, "Identifiants Incorrects", "Veuillez entrer les identifiants d'un compte enregistrer");}
    }
}

void loginScreenWidget::registerUser(){
    cout<<"coucou"<<endl;
    QDialog* dialog = new QDialog(this);
    dialog->setWindowTitle("Nouveau compte");
    // Use a layout allowing to have a label next to each field
    QFormLayout form(dialog);


    // Add the lineEdits with their respective labels
    QLineEdit* newUserName = new QLineEdit(dialog);
    QString label = QString("Nom de compte : ");
    form.addRow(label,newUserName);
    QLineEdit* newPassword = new QLineEdit(dialog);
    QString label2 = QString("Mot de passe : ");
    form.addRow(label2,newPassword);


    // Add some standard buttons (Cancel/Ok) at the bottom of the dialog
    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
                               Qt::Horizontal, dialog);
    form.addRow(&buttonBox);
    QObject::connect(&buttonBox, SIGNAL(accepted()), dialog, SLOT(accept()));
    QObject::connect(&buttonBox, SIGNAL(rejected()), dialog, SLOT(reject()));

    // Show the dialog as modal
    QString newID;
    QString newPW;

    if (dialog->exec() == QDialog::Accepted) {
        newID = newUserName->text();
        newPW = newPassword->text();
    }
    cout<<newID.toStdString()<<endl;
}

void loginScreenWidget::exit() {
    parent_->close();
}
