#include "teamhandlingwidget.h"
#include <QCoreApplication>
#include <QHeaderView>

TeamHandlingWidget::TeamHandlingWidget(MainWindow * parent):
    QWidget(parent), parent_(parent) {
    //-------------------------SIZE SETTINGS---------------------------
    this->setFixedHeight(720);
    this->setFixedWidth(1280);

    //----------------------BACKGROUND SETTINGS---------------------------
    QVBoxLayout * layout = new QVBoxLayout;
    QLabel * image = new QLabel(this);
    image->setPixmap(QPixmap(QCoreApplication::applicationDirPath() + "/images/Quidditch_pitch_hogwarts.jpg"));
    layout->addWidget(image);
    this->setLayout(layout);

    //---------------------MAIN CONTAINER WIDGET---------------------------
    QWidget * mainWidget = new QWidget(this);
    mainWidget->setFixedHeight(720);
    mainWidget->setFixedWidth(1280);
    QGridLayout * mainLayout = new QGridLayout(mainWidget);


    //--------------------TEAM DISPLAY-----------------------------


    vector<NonFieldPlayer *> playerList = parent_->getPlayers();
    int playersNumber = playerList.size();
    QTableWidget * playersDisplayer = new QTableWidget(playersNumber, 6, mainWidget);
    for (int i = 0; i< playersNumber; ++i){
        playersDisplayer->setItem(i,0,new QTableWidgetItem(QString::number(playerList[i]->getSpeed())));
        playersDisplayer->setItem(i,1,new QTableWidgetItem(QString::number(playerList[i]->getForce())));
        playersDisplayer->setItem(i,2,new QTableWidgetItem(QString::number(playerList[i]->getAgility())));
        playersDisplayer->setItem(i,3,new QTableWidgetItem(QString::number(playerList[i]->getReflexes())));
        playersDisplayer->setItem(i,4,new QTableWidgetItem(QString::number(playerList[i]->getPassPrecision())));
        QString iswounded;
        if(playerList[i]->isWounded()){
            iswounded = "Blessé";
        }
        else{
            iswounded = "Non Blessé";
        }
            playersDisplayer->setItem(i,5,new QTableWidgetItem(iswounded));
        playersDisplayer->setVerticalHeaderItem(i, new QTableWidgetItem("Joueur "+QString::number(i+1)));
    }

    int tableheight = 300;
    int tableWidth =  600;

    playersDisplayer->setSelectionMode(QAbstractItemView::NoSelection);
    playersDisplayer->setEditTriggers(QAbstractItemView::EditTriggers(0));
    playersDisplayer->setStyleSheet("QHeaderView::section { background-color : rgb(139,69,19); color:white;}");
    playersDisplayer->setHorizontalHeaderLabels(QString("Vitesse;Force;Agilité;Reflexes;Précision;État").split(";"));
    mainWidget->setFixedSize(tableWidth, tableheight);

    QPushButton * backButton = new QPushButton("Retour", mainWidget);
    backButton->setMinimumHeight(40);
    connect(backButton, SIGNAL(clicked()), this, SLOT(backToMenu()));

    QHeaderView * header = playersDisplayer->horizontalHeader();
    header->setSectionResizeMode(QHeaderView::Stretch);

    QHeaderView * header2 = playersDisplayer->verticalHeader();
    header2->setSectionResizeMode(QHeaderView::Stretch);

    mainLayout->addWidget(playersDisplayer);
    mainLayout->addWidget(backButton);
    mainWidget->move(parent_->width() / 2 - tableWidth / 2, parent_->height() / 2 - tableheight / 2);


}


void TeamHandlingWidget::backToMenu() {
    parent_->setNextScreen(MAINMENUSTATE);
}
