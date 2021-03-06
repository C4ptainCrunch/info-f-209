#include "infrastructurewidget.h"
#include <QHBoxLayout>
#include <QGridLayout>

#include <iostream>
using namespace std;

InfrastructureWidget::InfrastructureWidget(MainWindow * parent):
    QWidget(parent), parent_(parent) {

    //-------------------------SIZE SETTINGS---------------------------
    this->setFixedHeight(720);
    this->setFixedWidth(1280);

    //----------------------BACKGROUND SETTINGS---------------------------
    QVBoxLayout * layout = new QVBoxLayout;
    QLabel * image = new QLabel(this);
    image->setPixmap(QPixmap(ROOT_DIR + "/images/Quidditch_pitch_hogwarts.jpg"));
    layout->addWidget(image);
    //this->setLayout(layout);

    //---------------------MAIN CONTAINER WIDGET---------------------------
    mainWidget = new QWidget(this);
    mainWidget->setFixedHeight(720);
    mainWidget->setFixedWidth(1280);

    //------------------------INFIRMARY BUTTON ----------------------------
    QPushButton * infirmaryButton = new QPushButton(mainWidget);
    infirmaryButton->setFixedSize(128, 128);
    infirmaryButton->setStyleSheet("background-image : url(images/infirmaryLogo.jpg);");
    connect(infirmaryButton, SIGNAL(clicked()), this, SLOT(setInfirmary()));

    //---------------------TRAINING FIELD BUTTON ----------------------------
    QPushButton * trainingFieldButton = new QPushButton(mainWidget);
    trainingFieldButton->setFixedSize(128, 128);
    trainingFieldButton->setStyleSheet("background-image : url(images/trainingFieldLogo.jpg);");
    connect(trainingFieldButton, SIGNAL(clicked()), this, SLOT(setTrainingField()));

    //-------------------------FIELD BUTTON ---------------------------------
    QPushButton * fieldButton = new QPushButton(mainWidget);
    fieldButton->setFixedSize(128, 128);
    fieldButton->setStyleSheet("background-image : url(images/fieldLogo.jpg);");
    connect(fieldButton, SIGNAL(clicked()), this, SLOT(setField()));

    //-------------------------FIELD BUTTON ---------------------------------
    QPushButton * candyShopButton = new QPushButton(mainWidget);
    candyShopButton->setFixedSize(128, 128);
    candyShopButton->setStyleSheet("background-image : url(images/candyShopLogo.jpg);");
    connect(candyShopButton, SIGNAL(clicked()), this, SLOT(setCandyShop()));

    //-------------------------FIELD BUTTON ---------------------------------
    QPushButton * fanShopButton = new QPushButton(mainWidget);
    fanShopButton->setFixedSize(128, 128);
    fanShopButton->setStyleSheet("background-image : url(images/fanShopLogo.jpg);");
    connect(fanShopButton, SIGNAL(clicked()), this, SLOT(setFanShop()));
    //---------------------------LABEL---------------------------------------
    currentInfrastructureWidget = new QWidget(mainWidget);
    currentInfrastructureWidget->setFixedSize(600, 100);
    currentInfrastructureWidget->setStyleSheet("background-image : url(images/wood.jpg); border: 2px solid darkbrown; border-radius: 10px; padding: 0 8px;");

    currentInfrastructure = new QLabel(currentInfrastructureWidget);
    currentInfrastructure->setFixedWidth(600);
    currentInfrastructure->setFixedHeight(100);
    currentInfrastructure->setText("Nursery");
    currentInfrastructure->setAlignment(Qt::AlignHCenter);
    currentInfrastructure->setAlignment(Qt::AlignVCenter);
    currentInfrastructure->setStyleSheet("color : white; font-size : 50px;");

    QHBoxLayout * buttonsLayout = new QHBoxLayout();

    buttonsLayout->addWidget(infirmaryButton);
    buttonsLayout->addWidget(trainingFieldButton);
    buttonsLayout->addWidget(fieldButton);
    buttonsLayout->addWidget(candyShopButton);
    buttonsLayout->addWidget(fanShopButton);

    QPushButton * upgradeButton = new QPushButton("Upgrade", mainWidget);
    upgradeButton->setFixedHeight(50);
    QPushButton * downgradeButton = new QPushButton("Downgrade", mainWidget);
    downgradeButton->setFixedHeight(50);
    QHBoxLayout * gradeButtonsLayout = new QHBoxLayout();
    gradeButtonsLayout->addWidget(upgradeButton);
    gradeButtonsLayout->addWidget(downgradeButton);

    QGridLayout * mainLayout = new QGridLayout(mainWidget);
    QPushButton * backButton = new QPushButton("Back", mainWidget);
    connect(backButton, SIGNAL(clicked()), this, SLOT(backToMenu()));
    backButton->setFixedSize(100, 50);
    QWidget * temp2 = new QWidget(mainWidget);
    temp2->setFixedSize(100, 100);

    mainLayout->addWidget(backButton, 0, 0);
    mainLayout->addWidget(currentInfrastructureWidget, 0, 1);
    mainLayout->addWidget(temp2, 3, 2);
    mainLayout->addLayout(buttonsLayout, 1, 1);
    mainLayout->addLayout(gradeButtonsLayout, 2, 1);


}

void InfrastructureWidget::setTrainingField() {
    currentInfrastructure->hide();
    currentInfrastructure->setText("Training Field");
    currentInfrastructure->show();
}
void InfrastructureWidget::setInfirmary() {
    currentInfrastructure->hide();
    currentInfrastructure->setText("Nursery");
    currentInfrastructure->show();
}
void InfrastructureWidget::setField() {
    currentInfrastructure->hide();
    currentInfrastructure->setText("Field");
    currentInfrastructure->show();
}
void InfrastructureWidget::setFanShop() {
    currentInfrastructure->hide();
    currentInfrastructure->setText("Fanshop");
    currentInfrastructure->show();
}
void InfrastructureWidget::setCandyShop() {
    currentInfrastructure->hide();
    currentInfrastructure->setText("Candy Shop");
    currentInfrastructure->show();
}

void InfrastructureWidget::backToMenu() {
    parent_->setNextScreen(MAINMENUSTATE);
}
