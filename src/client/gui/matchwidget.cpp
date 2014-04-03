#include "matchwidget.h"
#include <iostream>
#include <cmath>

using namespace std;

MatchWidget::MatchWidget(Match * startingMatch, MainWindow * parent):
    QWidget(parent) {
    parent_ = parent;
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


    //----------------------CUSTOM SIGNALS CONNECT-------------------------

    QObject::connect(parent_, SIGNAL(setMatch(Match *)), this, SLOT(setCurrentMatch(Match *)));


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

    //askMatchToServer();


    currentMatch_->getGrid(grid_);
    refreshField();
    mainWidget->show();


}

void MatchWidget::refreshField() {

    QLabel * label = new QLabel(fieldWidget);
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
    for (int i = 0; i < WIDTH; ++i) {
        for (int j = 0; j < LENGTH; ++j) {
            hexagon[i][j].setX(x);
            hexagon[i][j].setY(y);
            hexagon[i][j].setCorners();

            x += 18;
            if (grid_[i][j].type == USABLE) {
                if (grid_[i][j].player != 0) {
                    if (isCaseHighlighted(i, j)) {
                        painter.setOpacity(0.6);
                    }
                    else {
                        painter.setOpacity(1.0);
                    }
                    if (!grid_[i][j].player->isInGuestTeam()) {
                        painter.setBrush(QBrush(Qt::blue));
                    }
                    else {
                        painter.setBrush(QBrush(Qt::red));
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
                        painter.setBrush(QBrush(Qt::red));
                    }
                    else { //ballName == "G")
                        painter.setBrush(QBrush(Qt::yellow));
                    }
                }
                else {
                    painter.setBrush(*grass);
                }
                painter.drawPolygon(hexagon[i][j].hexagon_);

            }
            else if (grid_[i][j].type == GOAL) {
                painter.setBrush(QBrush(QColor(171, 171, 171)));
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
    mainWidget->show();
}


bool MatchWidget::isCaseHighlighted(unsigned x, unsigned y) {
    for (size_t i = 0; i < highlightedCases.size(); ++i) {
        if ((highlightedCases[i].x == x) && (highlightedCases[i].y == y)) {
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
            cout << "ROW : " << row << " COL : " << column << endl;
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

}

void MatchWidget::surrender() {
    sviews::surrender(parent_->getSocket());
}
void MatchWidget::mousePressEvent(QMouseEvent * event) {
    if (event->button() == Qt::RightButton) {
        highlightedCases.clear();
        refreshField();
    }
    else {
        Position clickedCase = getCase(event);
        if (highlightedCases.empty() or isCloseCase(clickedCase, highlightedCases[highlightedCases.size() - 1], 0)) {
            highlightedCases.push_back(clickedCase);
            cout << highlightedCases.size() << endl;
        }
        refreshField();
    }
}

void MatchWidget::nextPlayer() {
    chosenWays.push_back(highlightedCases);
    highlightedCases.clear();
    refreshField();
}
