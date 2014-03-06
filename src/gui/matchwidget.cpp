#include "matchwidget.h"

MatchWidget::MatchWidget(QWidget *parent) :
    QWidget(parent)
{

    //-------------------------SIZE SETTINGS---------------------------
    this->setFixedHeight(720);
    this->setFixedWidth(1280);

    //----------------------BACKGROUND SETTINGS---------------------------
    QVBoxLayout *layout = new QVBoxLayout;
    QLabel * image = new QLabel(this);
    image->setPixmap(QPixmap(QCoreApplication::applicationDirPath() + "/images/Quidditch_pitch_hogwarts.jpg"));
    layout->addWidget(image);
    this->setLayout(layout);

    //---------------------MAIN CONTAINER WIDGET---------------------------
    QWidget* mainWidget = new QWidget(this);
    mainWidget->setFixedHeight(720);
    mainWidget->setFixedWidth(1280);
    QGridLayout* mainLayout = new QGridLayout(mainWidget);

    fieldWidget  = new QFrame(mainWidget);
    fieldWidget->setFixedSize(QSize(600,400));
    fieldWidget->setLineWidth(2);
    fieldWidget->setFrameStyle(QFrame::Box);
    fieldWidget->move(mainWidget->width()/2-fieldWidget->width()/2,mainWidget->height()/2-fieldWidget->height()/2);
    QPalette* palette = new QPalette();
    palette->setColor(QPalette::Foreground,Qt::darkRed);
    fieldWidget->setStyleSheet("background-image : url(images/grass2.jpg)");
    //palette->setColor(QPalette::Background,Qt::white);
    fieldWidget->setPalette(*palette);
    fieldWidget->setAutoFillBackground( true );
    //QPushButton* test = new QPushButton("Coucou",fieldWidget);

    //---------------------FIELD REPRESENTATION----------------------------
    QGraphicsScene* scene = new QGraphicsScene(fieldWidget);

    Hexagon hexagon[WIDTH][LENGHT];

    double x = 26;
    double y = 0;
    int delta = 1/2;
    bool pair = true;
    for(int i = 0; i<WIDTH;++i){
        for(int j = 0; j<LENGHT; ++j){
            hexagon[i][j].setX(x);
            hexagon[i][j].setY(y);
            hexagon[i][j].setCorners();
            //hexagon[i][j].setStylesheet("background-image : url(images/grass2.jpg)");

            x += 18;

            double diameterFactor = 46.0/100.0;

            double result = pow(i-WIDTH/2.0, 2)/pow(diameterFactor*WIDTH, 2);
            result+= pow(j-LENGHT/2.0, 2)/pow(diameterFactor*LENGHT, 2);
            if (i%2 !=0){
                result -= delta;
            }
            if (result<1){
                hexagon[i][j].update();
                scene->addPolygon(hexagon[i][j].hexagon_);
                hexagon[i][j].update();
                scene->update();
            }
        }
        y += 15;
        if( pair){
            x = 35;
        }
        else{
            x = 26;
        }
        pair = !pair;
    }


    QGraphicsView vue(scene);
    vue.setFixedSize(1200,1200);
    //vue.show();
    //mainLayout->addWidget(fieldWidget,1,1);
    mainWidget->setLayout(mainLayout);
    //fieldWidget->move(400,400);
    mainWidget->show();


}

MatchWidget::~MatchWidget(){}
