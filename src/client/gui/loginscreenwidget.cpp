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
    creditsButton = new QPushButton("Credits", fields);
    QObject::connect(creditsButton, SIGNAL(clicked()), this, SLOT(showCredits()));

    connectButton = new QPushButton("Connect", fields);
    QObject::connect(connectButton, SIGNAL(clicked()), this, SLOT(logIn()));

    registerButton = new QPushButton("Register", fields);
    QObject::connect(registerButton, SIGNAL(clicked()),this, SLOT(registerUser()));

    quitButton = new QPushButton("Quit", fields);
    QObject::connect(quitButton, SIGNAL(clicked()), this, SLOT(exit()));

    //-----------------------CUSTOM SIGNALS CONNECTION--------------------

    QObject::connect(parent_,SIGNAL(loginSuccess()),this,SLOT(acceptLogin()));
    QObject::connect(parent_, SIGNAL(loginFailure(int)),this,SLOT(refuseLogin(int)));
    QObject::connect(parent_, SIGNAL(registerSuccess()),this,SLOT(acceptRegister()));
    QObject::connect(parent_, SIGNAL(registerFailure(int)),this,SLOT(refuseRegister(int)));


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
                             "Dans le cadre du cours INFO-F-209\n"
                             "En fait, Quidditch c'est uidditch fait par Qt");

}


void loginScreenWidget::logIn() {
    QString username = usernameLine->text();
    QString password = passLine->text();
    if ((username.isEmpty() && password.isEmpty())or((username == "username") && (password == "password"))) {
        QMessageBox::warning(this, "Champs Vides", "Vous n'avez pas fourni de nom d'utilisateur et de mot de passe");
    }
    else {
        //TODO VERIFY ID/PASSWORD
        sviews::login(*parent_->getSocket(), username.toStdString(), password.toStdString());
        connectButton->setDisabled(true);
        connectButton->setStyleSheet("color : black;");
        registerButton->setDisabled(true);
        creditsButton->setDisabled(true);

        //parent_->setNextScreen(MAINMENUSTATE);
        //else {QMessageBox::warning(this, "Identifiants Incorrects", "Veuillez entrer les identifiants d'un compte enregistré");}
    }
}

void loginScreenWidget::acceptLogin(){
    parent_->setNextScreen(MAINMENUSTATE);
}

void loginScreenWidget::refuseLogin(int errorCode){
    if (errorCode == 300){
        QMessageBox::warning(this, "Identifiants Incorrects", "Veuillez entrer les identifiants d'un compte enregistré");
    }
    else if (errorCode == 401){
        QMessageBox::warning(this, "Identifiants Incorrects", "Mauvais mot de passe");
    }
    else{
        QMessageBox::warning(this, "Identifiants Incorrects", "Tu n'as pas des projets à terminer?");
    }

    connectButton->setStyleSheet("color : white;");
}

void loginScreenWidget::acceptRegister(){
    parent_->setNextScreen(MAINMENUSTATE);
}

void loginScreenWidget::refuseRegister(int errorCode){
    if (errorCode == 402){
        QMessageBox::warning(this, "Identifiants Incorrects", "Ce compte est déjà enregistré! Veuillez choisir un nouvel identifiant");
    }
    else{
        QMessageBox::warning(this, "Identifiants Incorrects", "Le serveur ne comprend rien");
    }
    registerButton->setStyleSheet("color : white;");
}

void loginScreenWidget::registerUser(){
    registerButton->setStyleSheet("color : black;");
    QDialog* dialog = new QDialog(this);
    dialog->setWindowTitle("Nouveau compte");

    QFormLayout form(dialog);

    QLineEdit* newUserName = new QLineEdit(dialog);
    QString label = QString("Nom de compte : ");
    form.addRow(label,newUserName);

    QLineEdit* newPassword = new QLineEdit(dialog);
    newPassword->setEchoMode(QLineEdit::Password);
    QString label2 = QString("Mot de passe : ");
    form.addRow(label2,newPassword);

    QLineEdit* newManagerName = new QLineEdit(dialog);
    QString label3 = QString("Nom de manager : ");
    form.addRow(label3,newManagerName);


    // Add some standard buttons (Cancel/Ok) at the bottom of the dialog
    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
                               Qt::Horizontal, dialog);
    form.addRow(&buttonBox);
    QObject::connect(&buttonBox, SIGNAL(accepted()), dialog, SLOT(accept()));
    QObject::connect(&buttonBox, SIGNAL(rejected()), dialog, SLOT(reject()));
    registerButton->setStyleSheet("color : white;");

    // Show the dialog as modal
    QString newID;
    QString newPW;
    QString newName;

    if (dialog->exec() == QDialog::Accepted) {
        newID = newUserName->text();
        newPW = newPassword->text();
        newName = newManagerName->text();

        sviews::signup(*parent_->getSocket(), newID.toStdString(), newName.toStdString(), newPW.toStdString());
    }
}

void loginScreenWidget::exit() {
    parent_->close();
}