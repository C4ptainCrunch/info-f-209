#include "matchwidget.h"
#include <iostream>
#include <cmath>

using namespace std;

MatchWidget::MatchWidget(QWidget * parent):
    QWidget(parent) {

    //-------------------------SIZE SETTINGS---------------------------
    this->setFixedHeight(720);
    this->setFixedWidth(1280);

    //----------------------BACKGROUND SETTINGS---------------------------
    QVBoxLayout * layout = new QVBoxLayout;
    QLabel * image = new QLabel(this);
    image->setPixmap(QPixmap(QCoreApplication::applicationDirPath() + "/images/Quidditch_pitch_hogwarts.jpg"));
    layout->addWidget(image);
    //this->setLayout(layout);


    //---------------------MAIN CONTAINER WIDGET---------------------------
    mainWidget = new QWidget(this);
    mainWidget->setFixedHeight(720);
    mainWidget->setFixedWidth(1280);
    QGridLayout * mainLayout = new QGridLayout(mainWidget);

    //------------------------SCORE SETTINGS--------------------------------
    QLabel * ownScore = new QLabel("VOUS : 0", mainWidget);
    ownScore->setFixedSize(200, 75);
    QFont font;
    font.setPointSize(17);
    ownScore->setStyleSheet(" font-weight: bold; font-size: 18pt; color : red;");
    ownScore->setAlignment(Qt::AlignBottom | Qt::AlignJustify);
    ownScore->setWordWrap(true);
    ownScore->setFont(font);
    ownScore->move(100, 50);
    ownScore->show();

    opponentScore = new QLabel("ADVERSAIRE : 0", mainWidget);
    opponentScore->setFixedSize(200, 75);
    opponentScore->setAlignment(Qt::AlignBottom | Qt::AlignJustify);
    opponentScore->setStyleSheet(" font-weight: bold; font-size: 18pt; color : red;");
    opponentScore->setWordWrap(true);
    opponentScore->setFont(font);
    opponentScore->move(1000, 50);
    opponentScore->show();

    //---------------------FIELD CONTAINER WIDGET--------------------------
    fieldWidget  = new QFrame(mainWidget);
    //fieldWidget->setLineWidth(2);
    //fieldWidget->setFrameStyle(QFrame::Box);
    /*
       QPalette* palette = new QPalette();
       palette->setBrush(QPalette::Foreground,QBrush(QImage("images/wood.jpg")));
       palette->setColor(QPalette::Background,Qt::white);
       fieldWidget->setPalette(*palette);
       fieldWidget->setAutoFillBackground( true );
     */

    //---------------------FIELD REPRESENTATION----------------------------

    fieldWidget->setFixedSize(QSize(LENGHT*20, WIDTH*17));
    QWidget* temp = new QWidget(fieldWidget);

    temp->setFixedSize((mainWidget->height()-WIDTH*20)/2,(mainWidget->width()-LENGHT*20)/2);
    QLabel * label = new QLabel(fieldWidget);
    QPixmap * pixmap = new QPixmap(LENGHT*20, WIDTH*17);
    mainLayout->setRowMinimumHeight(0,100);
    mainLayout->addWidget(temp,0,0);
    mainLayout->addWidget(fieldWidget,1,1);

    QPushButton* turnEndButton = new QPushButton("Fin du tour",mainWidget);
    turnEndButton->setMinimumHeight(30);
    mainLayout->addWidget(turnEndButton, 2,2);

    QPushButton* surrenderButton = new QPushButton("Abandonner",mainWidget);
    surrenderButton->setMinimumHeight(30);
    mainLayout->addWidget(surrenderButton, 2,3);

    pixmap->fill(Qt::transparent);

    QPainter painter(pixmap);
    painter.setBrush(QBrush(Qt::darkGreen));
    Hexagon hexagon[WIDTH][LENGHT];
    QBrush * grass = new QBrush(QImage("images/grass.jpg"));

    generateGrid();

    //TODO adapter aux modèles

    double x = 0;
    double y = 0;
    bool pair = true;
    for (int i = 0; i < WIDTH; ++i) {
        //<<i<<endl;
        for (int j = 0; j < LENGHT; ++j) {
            //cout<<"MAX : "<<WIDTH<<" "<<LENGHT<<" X : "<<i<<" Y : "<<j<<endl;
            cout<<grid_[i][j]<<" ";
            hexagon[i][j].setX(x);
            hexagon[i][j].setY(y);
            hexagon[i][j].setCorners();

            x += 18;
            painter.setBrush(*grass);
            if(grid_[i][j] != 9){
                switch(grid_[i][j]){
                    case -1:
                        painter.setBrush(QBrush(Qt::yellow));
                        break;
                    case 1:
                        painter.setBrush(QBrush(Qt::red));
                        break;
                    case 2:
                        painter.setBrush(QBrush(Qt::blue));
                        break;
                    case 3:
                        painter.setBrush(QBrush(Qt::white));
                        break;
                    case 4:
                        painter.setBrush(QBrush(Qt::black));
                        break;
                    case 5:
                        painter.setBrush(QBrush(QColor("darkGrey")));
                        break;
                    case 6:
                        painter.setBrush(QBrush(QColor("brown")));
                        break;
                    case 7:
                        painter.setBrush(QBrush(QColor("darkRed")));
                        break;
                }
                painter.drawPolygon(hexagon[i][j].hexagon_);
            }
        }
        cout<<endl;
        y += 15;
        if (pair) {
            x = 35;
        }
        else {
            x = 26;
        }
        pair = !pair;
    }
    //cout<<"coucou";
    //cout<<"CACA"<<endl;
    label->setPixmap(*pixmap);


    //mainLayout->addWidget(fieldWidget,1,1);
    //cout<<"ICI"<<endl;
    //mainWidget->setLayout(mainLayout);
    //cout<<"LA"<<endl;
    //fieldWidget->move(200,200);
    grid_[13][49] = 7;
    refreshField();
    mainWidget->show();


}

void MatchWidget::mousePressEvent ( QMouseEvent * event ){


    double hexagonHeight = 18;
    double hexagonWidth = 15;
    double halfHeight = hexagonHeight / 2;
    int startHeight = 103;
    int startWidth = 144;
    cout<<"start : "<<startHeight<<endl;
    cout<<"ROW : "<<(event->y()-144)/15<<" COL : "<<(event->x()-103)/18<<endl;

    if(event->x()>startHeight && event->x()<1200){
        if(event->y()>startWidth && event->y()<580){

            // These will represent which box the mouse is in, not which hexagon!
            int row = (event->y()-startWidth) / hexagonWidth;
            int column;

            bool rowIsOdd = row % 2 == 0;

            // Is the row an even number?
            if (rowIsOdd)
                column = ((event->x() -startHeight)/ hexagonHeight);
            else
                column = ((event->x() -startHeight + halfHeight) / hexagonHeight);
            cout<<"ROW : "<<row<<" COL : "<<column<<endl;
            cout<<grid_[row+1][column]<<endl;

        }
    }


}

void MatchWidget::generateGrid() {
    /*
     *TO REMOVE , HAVE TO USE THE ONE FROM MODELS
     *
     */


    double diameterFactor = 46.0 / 100.0; // Normalement c'est la moitié de la longueur/largeur
    int delta = 1 / 2; //Delta qui permet d'éviter les bugs lors de l'affichage de la matrice


    for (int i = 0; i < WIDTH; ++i) {
        for (int j = 0; j < LENGHT; ++j) {
            grid_[i][j] = 0;
            // equation d'une ellipse non centrée : (x-h)²/a² + (x-k)²/b²
            //avec x = i, h et k sont les coord du centre, a et b les demi longueurs de l'ellipse
            double result = pow(i - WIDTH / 2.0, 2) / pow(diameterFactor * WIDTH, 2);
            result += pow(j - LENGHT / 2.0, 2) / pow(diameterFactor * LENGHT, 2);
            if (i % 2 != 0) {
                result -= delta;
            }
            if (result > 1) { //Si on est à l'extérieur de l'ellipse
                grid_[i][j] = 9;
            }


            //----------------------------GOALS---------------------------------
            if (i == WIDTH / 2) {
                if (j == LENGHT / 15 + LENGHT / 20 or j == LENGHT * 14 / 15 - LENGHT / 20) {
                    grid_[i][j] = -1; //goal central
                }
                else if (j == 2 * LENGHT / 15) {
                    grid_[i][j] = 1;
                }
                else if (j == 13 * LENGHT / 15) {
                    grid_[i][j] = 1;
                }
                else if (j == 7 * LENGHT / 30) {
                    grid_[i][j] = 2;
                }
                else if (j == 23 * LENGHT / 30) {
                    grid_[i][j] = 2;
                }
                else if (j == 5 * LENGHT / 30) {
                    grid_[i][j] = 3;

                }
                else if (j == 25 * LENGHT / 30) {
                    grid_[i][j] = 3;
                }
            }
            else if (i == WIDTH / 2 - WIDTH / 15) {
                if (j == 2 * LENGHT / 15 or j == 13 * LENGHT / 15) {
                    grid_[i][j] = -1; //goals latéraux
                }
                else if (j == 5 * LENGHT / 30) {
                    grid_[i][j] = 4;

                }
                else if (j == 25 * LENGHT / 30) {
                    grid_[i][j] = 4;
                }
            }
            else if (i == WIDTH / 2 + WIDTH / 15) {
                if (j == 2 * LENGHT / 15 or j == 13 * LENGHT / 15) {
                    grid_[i][j] = -1; //goals latéraux
                }
                else if (j == 5 * LENGHT / 30) {
                    grid_[i][j] = 5;

                }
                else if (j == 25 * LENGHT / 30) {
                    grid_[i][j] = 5;
                }
            }
            else if (i == WIDTH / 2 - WIDTH / 30) {
                if (j == 6 * LENGHT / 30) {
                    grid_[i][j] = 6;

                }
                else if (j == 24 * LENGHT / 30) {
                    grid_[i][j] = 6;
                }

            }
            else if (i == WIDTH / 2 + WIDTH / 30) {
                if (j == 6 * LENGHT / 30) {
                    grid_[i][j] = 7;

                }
                else if (j == 24 * LENGHT / 30) {
                    grid_[i][j] = 7;
                }
            }

        //cout<<grid_[i][j];
        }
        //cout<<endl;
    }

}

void MatchWidget::refreshField(){

    QLabel * label = new QLabel(fieldWidget);
    QPixmap * pixmap = new QPixmap(LENGHT*20, WIDTH*17);
    pixmap->fill(Qt::transparent);

    QPainter painter(pixmap);
    painter.setBrush(QBrush(Qt::darkGreen));
    Hexagon hexagon[WIDTH][LENGHT];
    QBrush * grass = new QBrush(QImage("images/grass.jpg"));


    double x = 0;
    double y = 0;
    bool pair = true;
    for (int i = 0; i < WIDTH; ++i) {
        //cout<<i<<endl;
        for (int j = 0; j < LENGHT; ++j) {
            //cout<<"MAX : "<<WIDTH<<" "<<LENGHT<<" X : "<<i<<" Y : "<<j<<endl;
            cout<<grid_[i][j]<<" ";
            hexagon[i][j].setX(x);
            hexagon[i][j].setY(y);
            hexagon[i][j].setCorners();

            x += 18;
            painter.setBrush(*grass);
            if(grid_[i][j] != 9){
                switch(grid_[i][j]){
                    case -1:
                        painter.setBrush(QBrush(Qt::yellow));
                        break;
                    case 1:
                        painter.setBrush(QBrush(Qt::red));
                        break;
                    case 2:
                        painter.setBrush(QBrush(Qt::blue));
                        break;
                    case 3:
                        painter.setBrush(QBrush(Qt::white));
                        break;
                    case 4:
                        painter.setBrush(QBrush(Qt::black));
                        break;
                    case 5:
                        painter.setBrush(QBrush(QColor("darkGrey")));
                        break;
                    case 6:
                        painter.setBrush(QBrush(QColor("brown")));
                        break;
                    case 7:
                        painter.setBrush(QBrush(QColor("darkRed")));
                        break;
                }
                painter.drawPolygon(hexagon[i][j].hexagon_);
            }
        }
        cout<<endl;
        y += 15;
        if (pair) {
            x = 35;
        }
        else {
            x = 26;
        }
        pair = !pair;
    }
    label->setPixmap(*pixmap);
    mainWidget->show();
}


MatchWidget::~MatchWidget() {}
