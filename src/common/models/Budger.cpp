#include "Budger.h"

using namespace std;

Budger::Budger(): Ball(4), hitWay_() {
    srand(time(NULL));
}

Budger::Budger(int speed, Position position): Ball(speed, position) {}

Budger::Budger(JsonValue * json) {

    JsonDict* ball_dict = JDICT(json);
    if (ball_dict == NULL) {
        throw ModelUnserializationError(string(__FUNCTION__) + " in " + string(__FILE__) + ":" + to_string(__LINE__));
    }

    JsonInt * speed_int = JINT((*ball_dict)["speed"]);
    if (speed_int == NULL) {
        throw ModelUnserializationError(string(__FUNCTION__) + " in " + string(__FILE__) + ":" + to_string(__LINE__));
    }

    int speed = *speed_int;

    JsonList * position_list = JLIST((*ball_dict)["position"]);
    if (position_list == NULL) {
        throw ModelUnserializationError(string(__FUNCTION__) + " in " + string(__FILE__) + ":" + to_string(__LINE__));
    }

    JsonInt * x_int = JINT((*position_list)[0]);
    JsonInt * y_int = JINT((*position_list)[1]);

    if (x_int == NULL) {
        throw ModelUnserializationError(string(__FUNCTION__) + " in " + string(__FILE__) + ":" + to_string(__LINE__));
    }

    if (y_int == NULL) {
        throw ModelUnserializationError(string(__FUNCTION__) + " in " + string(__FILE__) + ":" + to_string(__LINE__));
    }

    Position position;
    position.x = *x_int;
    position.y = *y_int;

    new (this)Budger(speed, position);
}


Budger::~Budger() {}

Position Budger::autoMove(const Case grid[WIDTH][LENGTH]) {
    Position nextPosition;
    int next = rand() % 6;
    nextPosition = nextCase(position_, next, grid);
    if (grid[nextPosition.x][nextPosition.y].type == USABLE) {
        if (grid[nextPosition.x][nextPosition.y].ball == 0) {
            return nextPosition;
        }
    }
    for (int i = 0; i < 5; i++) {
        next = (next + 1) % 6;
        nextPosition = nextCase(position_, next, grid);
        if (grid[nextPosition.x][nextPosition.y].type == USABLE) {
            if (grid[nextPosition.x][nextPosition.y].ball == 0) {
                return nextPosition;
            }
        }
    }
    return position_;

}

void Budger::isHit(const char direction, const int power, const Case grid[WIDTH][LENGTH]) {
    Way way;
    for (int i = 0; i < power; i++) {
        way.push_back(nextCase(position_, direction, grid));
    }
    hitWay_ = way;
}

void Budger::hitPlayer(Player * player, int power) {
    if (1 == rand() % 20) {
        player->setWoundState(true);
    }
}

std::string Budger::getName() {
    return "B";
}

Way Budger::getHitWay() const {
    return hitWay_;
}

Budger::operator JsonDict() const {
    JsonDict r;
    r.add("speed", new JsonInt(speed_));
    JsonList * position = new JsonList();
    position->add(new JsonInt(position_.x));
    position->add(new JsonInt(position_.y));
    r.add("position", position);
    return r;
}
