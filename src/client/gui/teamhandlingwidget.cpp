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
    int playersNumber = 7;
    QTableWidget * playersDisplayer = new QTableWidget(playersNumber, 6, mainWidget);
    //QTableWidgetItem* items[7][5];
    if (playersNumber < 7) {}
    int tableheight = 300;
    int tableWidth =  600;

    QTableWidgetItem * item = new QTableWidgetItem();
    playersDisplayer->setItem(0, 0, item);
    playersDisplayer->setSelectionMode(QAbstractItemView::NoSelection);
    playersDisplayer->setEditTriggers(QAbstractItemView::EditTriggers(0));
    //QString path = QCoreApplication::applicationDirPath() + "/images/wood.jpg";
    playersDisplayer->setStyleSheet("QHeaderView::section { background-color : rgb(139,69,19); color:white;}");
    playersDisplayer->setVerticalHeaderItem(0, new QTableWidgetItem("Joueur 1"));
    playersDisplayer->setHorizontalHeaderLabels(QString("Vitesse;Force;Agilité;Reflexes;Précision;État").split(";"));
    item->setText("Hello world!");
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
