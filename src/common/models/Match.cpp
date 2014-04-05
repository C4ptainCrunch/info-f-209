#include "Match.h"

using namespace std;

Match::Match(Club * hostClub, Club * guestClub) {
    score_[0] = 0;
    score_[1] = 0;
    srand(time(NULL));
    clubs_[host] = hostClub;
    clubs_[guest] = guestClub;

    goldenSnitch_ = GoldenSnitch();
    quaffle_ = Quaffle();
    budgers_[0] = Budger();
    budgers_[1] = Budger();
    generateGrid();
    ready_[0] = false;
    ready_[1] = false;

}

Match::Match(Club * hostClub, Club * guestClub, GoldenSnitch goldenSnitch, Quaffle quaffle, Budger budger1, Budger budger2, int score[2], bool endGame) {
    score_[0] = score[0];
    score_[1] = score[1];
    srand(time(NULL));
    clubs_[host] = hostClub;
    clubs_[guest] = guestClub;

    goldenSnitch_ = goldenSnitch;
    quaffle_ = quaffle;
    budgers_[0] = budger1;
    budgers_[1] = budger2;

    double diameterFactor = 46.0 / 100.0; // Normalement c'est la moitié de la longueur/largeur
    int delta = 1 / 2; //Delta qui permet d'éviter les bugs lors de l'affichage de la matrice

    for (int i = 0; i < WIDTH; ++i) {
        for (int j = 0; j < LENGTH; ++j) {
            grid_[i][j].type = USABLE;
            // equation d'une ellipse non centrée : (x-h)²/a² + (x-k)²/b²
            //avec x = i, h et k sont les coord du centre, a et b les demi longueurs de l'ellipse
            double result = pow(i - WIDTH / 2.0, 2) / pow(diameterFactor * WIDTH, 2);
            result += pow(j - LENGTH / 2.0, 2) / pow(diameterFactor * LENGTH, 2);
            if (i % 2 != 0) {
                result -= delta;
            }
            if (result > 1) { //Si on est à l'extérieur de l'ellipse
                grid_[i][j].type = VOID;
            }
            //----------------------------GOALS---------------------------------
            if (i == WIDTH / 2) {
                if (j == LENGTH / 15 + LENGTH / 20 or j == LENGTH * 14 / 15 - LENGTH / 20) {
                    grid_[i][j].type = GOAL; //goal central
                }
            }
            else if (i == WIDTH / 2 - WIDTH / 15) {
                if (j == 2 * LENGTH / 15 or j == 13 * LENGTH / 15) {
                    grid_[i][j].type = GOAL; //goals latéraux
                }
            }
            else if (i == WIDTH / 2 + WIDTH / 15) {
                if (j == 2 * LENGTH / 15 or j == 13 * LENGTH / 15) {
                    grid_[i][j].type = GOAL; //goals latéraux
                }
            }
        }
    }

    Position pos = goldenSnitch_.getPosition();
    grid_[pos.x][pos.y].ball = &goldenSnitch_;
    pos = quaffle_.getPosition();
    grid_[pos.x][pos.y].ball = &quaffle_;
    pos = budgers_[0].getPosition();
    grid_[pos.x][pos.y].ball = &budgers_[0];
    pos = budgers_[1].getPosition();
    grid_[pos.x][pos.y].ball = &budgers_[1];
    ready_[0] = false;
    ready_[1] = false;
}

Match::Match(JsonValue * json) {
    JsonDict * match = JDICT(json);

    if (match == NULL) {
        throw ModelUnserializationError(string(__FUNCTION__) + " in " + string(__FILE__) + ":" + to_string(__LINE__));
    }

    Club * hostClub = new Club((*match)["hostClub"]);
    Club * guestClub = new Club((*match)["guestClub"]);

    GoldenSnitch goldenSnitch((*match)["goldenSnitch"]);
    Quaffle quaffle((*match)["quaffle"]);
    Budger budger1((*match)["budger1"]);
    Budger budger2((*match)["budger2"]);

    JsonInt * score1 = JINT((*match)["score1"]);
    JsonInt * score2 = JINT((*match)["score2"]);

    if ((score1 == NULL) || (score2 == NULL)) {
        throw ModelUnserializationError(string(__FUNCTION__) + " in " + string(__FILE__) + ":" + to_string(__LINE__));
    }
    int score[] = {*score1, *score2};

    JsonBool * endGame_bool = JBOOL((*match)["endGame"]);
    if (endGame_bool == NULL) {
        throw ModelUnserializationError(string(__FUNCTION__) + " in " + string(__FILE__) + ":" + to_string(__LINE__));
    }
    bool endGame = *endGame_bool;
    new (this)Match(hostClub, guestClub, goldenSnitch, quaffle, budger1, budger2, score, endGame);

    JsonList * grid_list = JLIST((*match)["grid"]);
    if (grid_list == NULL) {
        throw ModelUnserializationError(string(__FUNCTION__) + " in " + string(__FILE__) + ":" + to_string(__LINE__));
    }

    for (int i = 0; i < grid_list->size(); i++) {
        JsonDict * kase = JDICT((*grid_list)[i]);
        if (kase == NULL) {
            throw ModelUnserializationError(string(__FUNCTION__) + " in " + string(__FILE__) + ":" + to_string(__LINE__));
        }
        JsonInt * x_int = JINT((*kase)["x"]);
        JsonInt * y_int = JINT((*kase)["y"]);
        if ((x_int == NULL) && (y_int == NULL)) {
            throw ModelUnserializationError(string(__FUNCTION__) + " in " + string(__FILE__) + ":" + to_string(__LINE__));
        }
        int x = *x_int;
        int y = *y_int;

        grid_[x][y] = Case::fromJson((*kase)["case"]);
    }
    ready_[0] = false;
    ready_[1] = false;
}

Match::~Match() {}

void Match::generateFieldPlayers() {
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 7; ++j) {
            NonFieldPlayer player = *(clubs_[i]->getTeam()->getPlayer(j));
            teams_[i][j] = FieldPlayer(player, 0, i);
            if (j == 0) {
                teams_[i][j].setRole(KEEPER);
            }
            else if (j > 0 and j <= 3) {
                teams_[i][j].setRole(CHASER);
            }
            else if (j > 3 and j <= 5) {
                teams_[i][j].setRole(BEATER);
            }
            else {
                teams_[i][j].setRole(SEEKER);
            }
        }

    }
}

void Match::generateGrid() {
    double diameterFactor = 46.0 / 100.0; // Normalement c'est la moitié de la longueur/largeur
    int delta = 1 / 2; //Delta qui permet d'éviter les bugs lors de l'affichage de la matrice

    generateFieldPlayers();

    for (int i = 0; i < WIDTH; ++i) {
        for (int j = 0; j < LENGTH; ++j) {
            grid_[i][j].type = USABLE;
            // equation d'une ellipse non centrée : (x-h)²/a² + (x-k)²/b²
            //avec x = i, h et k sont les coord du centre, a et b les demi longueurs de l'ellipse
            double result = pow(i - WIDTH / 2.0, 2) / pow(diameterFactor * WIDTH, 2);
            result += pow(j - LENGTH / 2.0, 2) / pow(diameterFactor * LENGTH, 2);
            if (i % 2 != 0) {
                result -= delta;
            }
            if (result > 1) { //Si on est à l'extérieur de l'ellipse
                grid_[i][j].type = VOID;
            }
            //----------------------------GOALS---------------------------------
            if (i == WIDTH / 2) {
                if (j == LENGTH / 15 + LENGTH / 20 or j == LENGTH * 14 / 15 - LENGTH / 20) {
                    grid_[i][j].type = GOAL; //goal central
                }
                else if (j == 2 * LENGTH / 15) {
                    grid_[i][j].player = &teams_[0][0];
                }
                else if (j == 13 * LENGTH / 15) {
                    grid_[i][j].player = &teams_[1][0];
                }
                else if (j == 7 * LENGTH / 30) {
                    grid_[i][j].player = &teams_[0][6];
                }
                else if (j == 23 * LENGTH / 30) {
                    grid_[i][j].player = &teams_[1][6];
                }
                else if (j == 5 * LENGTH / 30) {
                    grid_[i][j].player = &teams_[0][1];

                }
                else if (j == 25 * LENGTH / 30) {
                    grid_[i][j].player = &teams_[1][1];
                }
            }
            else if (i == WIDTH / 2 - WIDTH / 15) {
                if (j == 2 * LENGTH / 15 or j == 13 * LENGTH / 15) {
                    grid_[i][j].type = GOAL; //goals latéraux
                }
                else if (j == 5 * LENGTH / 30) {
                    grid_[i][j].player = &teams_[0][2];

                }
                else if (j == 25 * LENGTH / 30) {
                    grid_[i][j].player = &teams_[1][2];
                }
            }
            else if (i == WIDTH / 2 + WIDTH / 15) {
                if (j == 2 * LENGTH / 15 or j == 13 * LENGTH / 15) {
                    grid_[i][j].type = GOAL; //goals latéraux
                }
                else if (j == 5 * LENGTH / 30) {
                    grid_[i][j].player = &teams_[0][3];

                }
                else if (j == 25 * LENGTH / 30) {
                    grid_[i][j].player = &teams_[1][3];
                }
            }
            else if (i == WIDTH / 2 - WIDTH / 30) {
                if (j == 6 * LENGTH / 30) {
                    grid_[i][j].player = &teams_[0][4];

                }
                else if (j == 24 * LENGTH / 30) {
                    grid_[i][j].player = &teams_[1][4];
                }

            }
            else if (i == WIDTH / 2 + WIDTH / 30) {
                if (j == 6 * LENGTH / 30) {
                    grid_[i][j].player = &teams_[0][5];

                }
                else if (j == 24 * LENGTH / 30) {
                    grid_[i][j].player = &teams_[1][5];
                }
            }
            //--------------------------BALLS----------------------------------
            if (j == LENGTH / 2) {
                if (i == WIDTH / 5) {
                    grid_[i][j].ball = &budgers_[0];
                    budgers_[0].setPosition(i, j);
                }
                else if (i == 2 * WIDTH / 5) {
                    grid_[i][j].ball = &goldenSnitch_;
                    goldenSnitch_.setPosition(i, j);
                }
                else if (i == 3 * WIDTH / (5)) {
                    grid_[i][j].ball = &quaffle_;
                    quaffle_.setPosition(i, j);
                }
                else if (i == 4 * WIDTH / 5) {
                    grid_[i][j].ball = &budgers_[1];
                    budgers_[1].setPosition(i, j);
                }
            }
        }
    }

}

void Match::movePlayer(Position fromPos, Position toPos) {
    grid_[toPos.x][toPos.y].player = grid_[fromPos.x][fromPos.y].player;
    grid_[fromPos.x][fromPos.y].player = 0;
}

bool Match::newTurn() {
    Way playerWays[14];
    for (int i = 0; i < 7; i++) {
        playerWays[i] = playerWays_[0][i];
    }
    for (int i = 0; i < 7; i++) {
        playerWays[i + 7] = playerWays_[1][i];
    }
    bool moved = true;
    int turnNumber = 0;
    while (moved && !endGame_) {
        moved = false;
        Position nextPosition[14];
        for (int i = 0; i < 14; ++i) {
            if (playerWays[i].size() > turnNumber + 1) {
                if (grid_[playerWays[i][turnNumber + 1].x][playerWays[i][turnNumber + 1].y].player == 0) {
                    nextPosition[i] = playerWays[i][turnNumber + 1];
                    movePlayer(playerWays[i][turnNumber], playerWays[i][turnNumber + 1]);
                }
                else {
                    resolveConflict(nextPosition, playerWays, i, turnNumber);
                }
                moved = true;
            }
        }
        moveBalls(moved, turnNumber);
        ++turnNumber;
    }
    for (int i = 0; i < 7; i++) {
        playerWays_[0][i] = Way();
    }
    for (int i = 0; i < 7; i++) {
        playerWays_[1][i] = Way();
    }
    return endGame_;
}

void Match::moveBalls(bool & moved, int turnNumber) {
    //BUDGERS
    Position nextBallPos;
    for (int i = 0; i < 2; ++i) {
        nextBallPos = budgers_[i].autoMove(grid_);
        grid_[budgers_[i].getPosition().x][budgers_[i].getPosition().y].ball = 0;
        budgers_[i].setPosition(nextBallPos.x, nextBallPos.y);
        grid_[nextBallPos.x][nextBallPos.y].ball = &budgers_[i];
        if (grid_[nextBallPos.x][nextBallPos.y].player != 0) {
            // TODO set direction and power for isHit and hitPlayer.
            if (grid_[nextBallPos.x][nextBallPos.y].player->getRole() == BEATER) {
                int direction = rand() % 6;
                budgers_[i].isHit(direction, grid_[nextBallPos.x][nextBallPos.y].player->getForce(), grid_);
            }
            else {
                budgers_[i].hitPlayer(grid_[nextBallPos.x][nextBallPos.y].player, 0);
            }
        }
    }

    //GOLDENSNITCH
    nextBallPos = goldenSnitch_.autoMove(grid_);
    grid_[goldenSnitch_.getPosition().x][goldenSnitch_.getPosition().y].ball = 0;
    goldenSnitch_.setPosition(nextBallPos.x, nextBallPos.y);
    grid_[nextBallPos.x][nextBallPos.y].ball = &goldenSnitch_;
    if (grid_[nextBallPos.x][nextBallPos.y].player != 0) {
        if (grid_[nextBallPos.x][nextBallPos.y].player->getRole() == SEEKER) {
            endGame_ = true;
            // TODO vérifier pour les 150
            addPoint(grid_[nextBallPos.x][nextBallPos.y].player->isInGuestTeam(), 150);
        }
    }


}

void Match::resolveConflict(Position nextPosition[14], Way playerWays[14], int indexOne, int turnNumber) {
    FieldPlayer * playerOne = grid_[playerWays[indexOne][turnNumber + 1].x][playerWays[indexOne][turnNumber + 1].y].player; //joueur sur la case causant la merde
    FieldPlayer * playerTwo = grid_[playerWays[indexOne][turnNumber].x][playerWays[indexOne][turnNumber].y].player; //joueur qui vient foutre la merde
    if (playerOne->getForce() >= playerTwo->getForce()) {
        playerWays[indexOne].insert(playerWays[indexOne].begin() + turnNumber + 1, playerWays[indexOne][turnNumber]); //le joueur le plus faible perd un déplacement(le dernier)
        nextPosition[turnNumber] = playerWays[indexOne][turnNumber];
    }
    else if (playerOne->getForce() < playerTwo->getForce()) {
        int indexTwo = findIndex(nextPosition, playerWays[indexOne][turnNumber + 1]);
        // Faire reculer le joueur qui etait avancé et qui doit retourner à la position précédente
        nextPosition[indexTwo] = playerWays[indexTwo][turnNumber];
        movePlayer(playerWays[indexTwo][turnNumber + 1], playerWays[indexTwo][turnNumber]);
        playerWays[indexTwo].insert(playerWays[indexTwo].begin() + turnNumber + 1, playerWays[indexTwo][turnNumber]); //le joueur le plus faible perd un déplacement(le dernier)

        // Faire avancer le joueur qui a gagné
        nextPosition[indexOne] = playerWays[indexOne][turnNumber + 1];
        movePlayer(playerWays[indexOne][turnNumber], playerWays[indexOne][turnNumber + 1]);
    }
}

int Match::findIndex(Position nextPosition[14], Position position) {
    for (int i = 0; i < 14; ++i) {
        if (nextPosition[i] == position) {
            return i;
        }
    }
    return -1;
}


string Match::print() { //FOR TEST PURPOSES
    string c = "\033[0m";
    for (int i = 0; i < WIDTH; ++i) {
        if (i % 2 != 0) {
            c += " ";
        }
        for (int j = 0; j < LENGTH; ++j) {
            if (grid_[i][j].type == USABLE) {
                if (grid_[i][j].player != 0) {
                    if (!grid_[i][j].player->isInGuestTeam()) {
                        c += "\033[1;94m";
                    }
                    else {
                        c += "\033[1;91m";
                    }
                    if (grid_[i][j].player->getRole() == KEEPER) {
                        c += "G ";
                    }
                    else if (grid_[i][j].player->getRole() == CHASER) {
                        c += "P ";
                    }
                    else if (grid_[i][j].player->getRole() == SEEKER) {
                        c += "A ";
                    }
                    else if (grid_[i][j].player->getRole() == BEATER) {
                        c += "B ";
                    }
                    c += "\033[0m";
                }
                else if (grid_[i][j].ball != 0) {
                    c += "\033[1;93m";
                    c += grid_[i][j].ball->getName();
                    c += "\033[0m";
                    //<< typeid(grid_[i][j].ball).name();
                }
                else {
                    c += "\u2B21 ";
                }

            }
            else if (grid_[i][j].type == GOAL) {
                c += "\033[1;32m오\033[0m";
            }
            else {
                c += "\u2B22 ";
            }
            //cout<< matrix[i][j]<<" ";
        }
        c += "\n";
    }
    return c;
}

int * Match::getScore() {
    return score_;
}

int Match::addPoint(bool guestTeam, int delta) {
    score_[guestTeam] += delta;
    return score_[guestTeam];
}

void Match::getGrid(Case grid[WIDTH][LENGTH]) {
    for (int i = 0; i < WIDTH; i++) {
        for (int j = 0; j < LENGTH; j++) {
            grid[i][j] = grid_[i][j];
        }
    }
}

Club * * Match::getClubs() {
    return clubs_;
}

Match::operator JsonDict() const {
    JsonDict r;

    r.add("hostClub", new JsonDict(*(clubs_[0])));
    r.add("guestClub", new JsonDict(*(clubs_[1])));
    r.add("goldenSnitch", new JsonDict(goldenSnitch_));
    r.add("quaffle", new JsonDict(quaffle_));
    r.add("budger1", new JsonDict(budgers_[0]));
    r.add("budger2", new JsonDict(budgers_[1]));
    r.add("score1", new JsonInt(score_[0]));
    r.add("score2", new JsonInt(score_[1]));
    r.add("endGame", new JsonBool(endGame_));

    JsonList * grid = new JsonList();
    for (int i = 0; i < WIDTH; i++) {
        for (int j = 0; j < LENGTH; j++) {
            if (grid_[i][j].player != NULL) {
                JsonDict * kase = new JsonDict();
                kase->add("x", new JsonInt(i));
                kase->add("y", new JsonInt(j));
                kase->add("case", new JsonDict(grid_[i][j]));
                grid->add(kase);
            }
        }
    }
    r.add("grid", grid);

    return r;
}

bool Match::isGuest(Club * club) {
    if (clubs_[guest] == club) {
        return true;
    }
    else {
        return false;
    }
}

void Match::setWays(bool isGuest, Way playerWays[7]) {
    for (int i = 0; i < 7; i++) {
        playerWays_[isGuest][i] = playerWays[i];
    }
}

bool Match::setReady(bool isGuest) {
    ready_[isGuest] = true;
    if (ready_[!isGuest]) {
        ready_[0] = false;
        ready_[1] = false;
        return true;
    }
    return false;
}
