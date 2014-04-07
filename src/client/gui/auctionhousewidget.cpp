#include "auctionhousewidget.h"

AuctionHouseWidget::AuctionHouseWidget(MainWindow * parent):
    QWidget(parent), parent_(parent) {
    //-------------------------SIZE SETTINGS---------------------------
    this->setFixedHeight(720);
    this->setFixedWidth(1280);

    //----------------------BACKGROUND SETTINGS---------------------------
    QVBoxLayout * layout = new QVBoxLayout;
    QLabel * image = new QLabel(this);
    image->setPixmap(QPixmap(ROOT_DIR + "/images/Quidditch_pitch_hogwarts.jpg"));
    layout->addWidget(image);
    this->setLayout(layout);

    //---------------------MAIN CONTAINER WIDGET---------------------------
    QWidget * mainWidget = new QWidget(this);
    mainWidget->setFixedHeight(720);
    mainWidget->setFixedWidth(1280);


    QWidget * message = new QWidget(mainWidget);
    QGridLayout * messageLayout = new QGridLayout(message);
    message->setFixedSize(600, 300);
    message->move((mainWidget->width() - 600) / 2, (mainWidget->height() - 300) / 2);
    message->setStyleSheet("padding: 10px;"
                           "border-style: solid;"
                           "border-width: 3px;"
                           "border-radius: 7px; border : 4px solid black; background : url(images/wood.jpg);");
    QLabel * textMessage = new QLabel("Auction House is in construction!\n                         Come back later!", mainWidget);
    textMessage->setStyleSheet("color : white; font-size : 20px;");
    textMessage->setFixedWidth(570);
    textMessage->setFixedHeight(100);
    messageLayout->addWidget(textMessage);
    message->setLayout(messageLayout);
    //textMessage->move((mainWidget->width())/2-270,(mainWidget->height())/2-30);

    QGridLayout * mainLayout = new QGridLayout(mainWidget);

    QPushButton * backButton = new QPushButton("Back", mainWidget);
    backButton->setMinimumHeight(60);
    connect(backButton, SIGNAL(clicked()), this, SLOT(backToMenu()));

    mainLayout->addWidget(message);
    mainLayout->addWidget(backButton);
    mainWidget->setLayout(mainLayout);


}

void AuctionHouseWidget::backToMenu() {
    parent_->setNextScreen(MAINMENUSTATE);
}
