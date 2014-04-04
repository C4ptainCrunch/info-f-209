#include "matchwidget.h"
#include <iostream>
#include <cmath>

using namespace std;

MatchWidget::MatchWidget(Match * startingMatch, bool isGuest, int matchID, MainWindow * parent):
    QWidget(parent), parent_(parent), isGuest_(isGuest), matchID_(matchID) {
    //-----------------------MATCH INITIALISATION-----------------------
    currentMatch_ = startingMatch;

    //-------------------------SIZE SETTINGS---------------------------
    this->setFixedHeight(720);
    this->setFixedWidth(1280);

    //----------------------BACKGROUND SETTINGS---------------------------
    QVBoxLayout * layout = new QVBoxLayout;
    QLabel * image = new QLabel(this);
    image->setPixmap(QPixmap(QCoreApplication::applicationDirPath() + "/images/Quidditch_pitch_hogwarts.jpg"));
    layout->addWidget(image);


    //---------------------MAIN CONTAINER WIDGET---------------------------
    mainWidget = new QWidget(this);
    mainWidget->setFixedHeight(720);
    mainWidget->setFixedWidth(1280);
    QGridLayout * mainLayout = new QGridLayout(mainWidget);

    //------------------------SCORE SETTINGS--------------------------------
    QLabel * ownScore = new QLabel("VOUS : 0", mainWidget);
    ownScore->setFixedSize(250, 75);
    QFont font;
    font.setPointSize(17);
    ownScore->setStyleSheet(" font-weight: bold; font-size: 18pt; color : red;");
    ownScore->setAlignment(Qt::AlignBottom | Qt::AlignJustify);
    ownScore->setWordWrap(true);
    ownScore->setFont(font);
    ownScore->move(100, 50);
    ownScore->show();

    opponentScore = new QLabel("ADVERSAIRE : 0", mainWidget);
    opponentScore->setFixedSize(250, 75);
    opponentScore->setAlignment(Qt::AlignBottom | Qt::AlignJustify);
    opponentScore->setStyleSheet(" font-weight: bold; font-size: 18pt; color : red;");
    opponentScore->setWordWrap(true);
    opponentScore->setFont(font);
    opponentScore->move(1000, 50);
    opponentScore->show();

    //---------------------FIELD CONTAINER WIDGET--------------------------
    fieldWidget  = new QFrame(mainWidget);




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

    //----------------------BUTTONS SIGNALS CONNECT-------------------------
    QObject::connect(turnEndButton, SIGNAL(clicked()), this, SLOT(endTurn()));
    QObject::connect(surrenderButton, SIGNAL(clicked()), this, SLOT(surrender()));

    //----------------------CUSTOM SIGNALS CONNECT-------------------------

    QObject::connect(parent_, SIGNAL(setMatch(Match *)), this, SLOT(setCurrentMatch(Match *)));
    QObject::connect(parent_, SIGNAL(endMatch(int)), this, SLOT(endMatch(int)));
    //askMatchToServer();


    currentMatch_->getGrid(grid_);
    label = 0;
    refreshField();

    mainWidget->show();

}

void MatchWidget::refreshField() {
    this->hide();
    label = new QLabel(fieldWidget);
    QPixmap * pixmap = new QPixmap(LENGTH * 20, WIDTH * 17);
    pixmap->fill(Qt::transparent);

    QPainter painter(pixmap);
    Hexagon hexagon[WIDTH][LENGTH];
    QBrush * grass = new QBrush(QImage("images/grass.jpg"));

    int xlabelDifference = 22;
    int ylabelDifference = 7;
    double x = 0;
    double y = 0;
    bool pair = true;
    bool highlighted;
    bool chosen;
    for (int i = 0; i < WIDTH; ++i) {
        for (int j = 0; j < LENGTH; ++j) {
            highlighted = false;
            chosen = false;
            hexagon[i][j].setX(x);
            hexagon[i][j].setY(y);
            hexagon[i][j].setCorners();

            x += 18;
            if (grid_[i][j].type == USABLE) {
                if (isCaseHighlighted(i, j)) {
                    painter.setBrush(QBrush(QColor(71,158,158)));
                    highlighted = true;
                }
                else if(isInChosenWays(i,j)){
                    painter.setBrush(QBrush(QColor(85,18,201)));
                    chosen = true;
                }
                if (grid_[i][j].player != 0) {
                    if(!highlighted && !chosen){
                        if (grid_[i][j].player->isInGuestTeam() == isGuest_) {
                            painter.setBrush(QBrush(Qt::blue));
                        }
                        else {
                            painter.setBrush(QBrush(Qt::red));
                        }
                    }
                    if (grid_[i][j].player->getRole() == KEEPER) {
                        playerLabels_[grid_[i][j].player->isInGuestTeam()][KEEPER] = new QLabel("K", fieldWidget);
                        playerLabels_[grid_[i][j].player->isInGuestTeam()][KEEPER]->move(x - xlabelDifference, y - ylabelDifference);
                    }
                    else if (grid_[i][j].player->getRole() == CHASER) {
                        playerLabels_[grid_[i][j].player->isInGuestTeam()][CHASER] = new QLabel("C", fieldWidget);
                        playerLabels_[grid_[i][j].player->isInGuestTeam()][CHASER]->move(x - xlabelDifference, y - ylabelDifference);
                    }
                    else if (grid_[i][j].player->getRole() == SEEKER) {
                        playerLabels_[grid_[i][j].player->isInGuestTeam()][SEEKER] = new QLabel("S", fieldWidget);
                        playerLabels_[grid_[i][j].player->isInGuestTeam()][SEEKER]->move(x - xlabelDifference, y - ylabelDifference);
                    }
                    else if (grid_[i][j].player->getRole() == BEATER) {
                        playerLabels_[grid_[i][j].player->isInGuestTeam()][BEATER] = new QLabel("B", fieldWidget);
                        playerLabels_[grid_[i][j].player->isInGuestTeam()][BEATER]->move(x - xlabelDifference, y - ylabelDifference);
                    }
                }
                else if (grid_[i][j].ball != 0) {
                    string ballName = grid_[i][j].ball->getName();
                    if (ballName == "B") {
                        painter.setBrush(QBrush(Qt::black));
                    }
                    else if (ballName == "Q") {
                        painter.setBrush(QBrush(QColor(140,52,52)));
                    }
                    else { //ballName == "G"
                        painter.setBrush(QBrush(Qt::yellow));
                    }
                }
                else {
                    if(!highlighted && !chosen){
                        painter.setBrush(*grass);
                    }
                }
                if(highlighted){
                    painter.drawPolygon(hexagon[i][j].hexagon_);
                }
                else{
                    painter.drawPolygon(hexagon[i][j].hexagon_);
                }
            }
            else if (grid_[i][j].type == GOAL) {
                painter.setBrush(QBrush(QColor(64, 64, 72)));
                painter.drawPolygon(hexagon[i][j].hexagon_);
            }
        }
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

    this->show();
}

bool MatchWidget::isInChosenWays(unsigned x, unsigned y){
    for (int i = 0; i<chosenWays.size();++i){
        for (int j = 0; j<chosenWays[i].size();++j){
            if(chosenWays[i][j].x == x && chosenWays[i][j].y == y){
                return true;
            }
        }
    }
    return false;
}

bool MatchWidget::isCaseHighlighted(unsigned a, unsigned b) {
    for (size_t i = 0; i < highlightedCases.size(); ++i) {
        //cout<<" x:"<<highlightedCases[i].x<<" y:"<<highlightedCases[i].y<<" a:"<<a<<" b:"<<b<< endl;
        if ((highlightedCases[i].x == a) && (highlightedCases[i].y == b)) {
            return true;
        }
    }
    return false;
}

MatchWidget::~MatchWidget() {}


void MatchWidget::setCurrentMatch(Match * match) {

    currentMatch_ = match;
    Case grid[WIDTH][LENGTH];
    currentMatch_->getGrid(grid);

    refreshField();
}

Position MatchWidget::getCase(QMouseEvent * event) {
    int row = 0;
    int column = 0;
    double hexagonHeight = 18;
    double hexagonWidth = 15;
    double halfHeight = hexagonHeight / 2;
    int startHeight = 103;
    int startWidth = 144;

    if ((event->x() > startHeight) && (event->x() < 1200)) {
        if ((event->y() > startWidth) && (event->y() < 580)) {

            // These will represent which box the mouse is in, not which hexagon!
            row = (event->y() - startWidth) / hexagonWidth;
            bool rowIsOdd = row % 2 == 0;

            // Is the row an even number?
            if (rowIsOdd) {
                column = ((event->x() - startHeight) / hexagonHeight);
            }
            else {
                column = ((event->x() - startHeight + halfHeight) / hexagonHeight);
            }
            //cout << grid_[row + 1][column] << endl;
        }
    }
    Position mouseCase;
    mouseCase.x = row + 1;
    mouseCase.y = column;
    return mouseCase;
}

void MatchWidget::endTurn() {
    sviews::endTurn(parent_->getSocket(), chosenWays);
    chosenWays.clear();

}

void MatchWidget::surrender() {
    sviews::surrenders(parent_->getSocket(), matchID_);

}

void MatchWidget::mousePressEvent(QMouseEvent * event) {
    if (event->button() == Qt::RightButton) {
        highlightedCases.clear();
        refreshField();
    }
    else {
        Position clickedCase = getCase(event);
        if (highlightedCases.empty()){
            int i = clickedCase.x;
            int j = clickedCase.y;
            if(grid_[i][j].player!= 0 && grid_[i][j].player->isInGuestTeam() == isGuest_){
                highlightedCases.push_back(clickedCase);
            }
        }
        else{
            if(isCloseCase(clickedCase, highlightedCases[highlightedCases.size() - 1], 0)) {
                highlightedCases.push_back(clickedCase);
            }
            else if(highlightedCases[highlightedCases.size() - 1] == clickedCase){
                emit this->nextPlayer();
            }
        }
        refreshField();
    }
}

void MatchWidget::endMatch(int signal){
    QString message;
    switch(signal){
        case EndMatch::WIN:
            message = "Vous avez gagné!";
            break;
        case EndMatch::LOSE:
            message = "Vous avez perdu.";
            break;
        case EndMatch::SURRENDER_WIN:
            message = "Vous avez gagné. Votre adversaire a abandonné";
            break;
        case EndMatch::SURRENDER_LOSE:
            message = "Votre adversaire vous remercie d'avoir abandonné";
            break;
    }
    QMessageBox::information(this,"Fin du match",message,QMessageBox::Ok);
    parent_->setNextScreen(MAINMENUSTATE);


}

void MatchWidget::nextPlayer() {
    chosenWays.push_back(highlightedCases);
    highlightedCases.clear();
    refreshField();
}
