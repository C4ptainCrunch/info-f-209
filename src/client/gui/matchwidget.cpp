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

    //----------------------CUSTOM SIGNALS CONNECT-------------------------

    QObject::connect(parent_, SIGNAL(setMatch(Match*)), this, SLOT(setCurrentMatch(Match*)));

    //---------------------FIELD REPRESENTATION----------------------------

    fieldWidget->setFixedSize(QSize(LENGTH * 20, WIDTH * 17));
    QWidget * temp = new QWidget(fieldWidget);

    temp->setFixedSize((mainWidget->height() - WIDTH * 20) / 2, (mainWidget->width() - LENGTH * 20) / 2);
    mainLayout->setRowMinimumHeight(0, 100);
    mainLayout->addWidget(temp, 0, 0);
    mainLayout->addWidget(fieldWidget, 1, 1);

    QPushButton * turnEndButton = new QPushButton("Fin du tour", mainWidget);
    turnEndButton->setMinimumHeight(30);
    mainLayout->addWidget(turnEndButton, 2, 2);

    QPushButton * surrenderButton = new QPushButton("Abandonner", mainWidget);
    surrenderButton->setMinimumHeight(30);
    mainLayout->addWidget(surrenderButton, 2, 3);
    
    //askMatchToServer();

    refreshField();

    Case grid[WIDTH][LENGTH];
    currentMatch->getGrid(grid);
    refreshField(grid);
    mainWidget->show();


}

void MatchWidget::refreshField(Case grid[WIDTH][LENGTH], Position highlightedCase) {

    QLabel * label = new QLabel(fieldWidget);
    QPixmap * pixmap = new QPixmap(LENGTH * 20, WIDTH * 17);
    pixmap->fill(Qt::transparent);

    QPainter painter(pixmap);
    painter.setBrush(QBrush(Qt::darkGreen));
    Hexagon hexagon[WIDTH][LENGTH];
    QBrush * grass = new QBrush(QImage("images/grass.jpg"));

    double x = 0;
    double y = 0;
    bool pair = true;
    for (int i = 0; i < WIDTH; ++i) {
        //cout<<i<<endl;
        for (int j = 0; j < LENGTH; ++j) {
            //cout<<"MAX : "<<WIDTH<<" "<<LENGTH<<" X : "<<i<<" Y : "<<j<<endl;
            cout << grid_[i][j] << " ";
            hexagon[i][j].setX(x);
            hexagon[i][j].setY(y);
            hexagon[i][j].setCorners();

            x += 18;
            painter.setBrush(*grass);
            if (grid_[i][j] != 9) {
                if(i== highlightedCase.x and j==highlightedCase.y){
                    painter.setOpacity(0.6);
                }
                else{
                    painter.setOpacity(1.0);
                }
                switch (grid_[i][j]) {
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
        cout << endl;
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

void askMatchToServer(){
    //TODO
}

void setMatch(Match* match){
    currentMatch = match;

    Case grid[WIDTH][LENGTH];
    currentMatch->getGrid(grid);
    refreshField(grid);
}

Position MatchWidget::getCase(QMouseEvent * event){

    double hexagonHeight = 18;
    double hexagonWidth = 15;
    double halfHeight = hexagonHeight / 2;
    int startHeight = 103;
    int startWidth = 144;
    cout << "start : " << startHeight << endl;
    cout << "ROW : " << (event->y() - 144) / 15 << " COL : " << (event->x() - 103) / 18 << endl;

    if ((event->x() > startHeight) && (event->x() < 1200)) {
        if ((event->y() > startWidth) && (event->y() < 580)) {

            // These will represent which box the mouse is in, not which hexagon!
            int row = (event->y() - startWidth) / hexagonWidth;
            int column;

            bool rowIsOdd = row % 2 == 0;

            // Is the row an even number?
            if (rowIsOdd) {
                column = ((event->x() - startHeight) / hexagonHeight);
            }
            else {
                column = ((event->x() - startHeight + halfHeight) / hexagonHeight);
            }
            cout << "ROW : " << row << " COL : " << column << endl;
            cout << grid_[row + 1][column] << endl;

        }
    }
    Position mouseCase;
    mouseCase.x = row+1;
    mouseCase.y = column;
    return mouseCase;
}


void MatchWidget::mousePressEvent(QMouseEvent * event) {
    Position clickedCase = getCase(event);
    Case grid[WIDTH][LENGTH];
    currentMatch->getGrid(grid);
    refreshField(grid,clickedCase);



}
