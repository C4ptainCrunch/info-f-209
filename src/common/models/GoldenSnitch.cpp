#include "GoldenSnitch.h"

using namespace std;

GoldenSnitch::GoldenSnitch(): Ball(42) {
    srand(time(NULL));
}

GoldenSnitch::GoldenSnitch(int speed, Position position): Ball(speed, position){ }

GoldenSnitch::GoldenSnitch(JsonValue * json) {

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

    new (this)GoldenSnitch(speed, position);
}

GoldenSnitch::~GoldenSnitch() {}

Position GoldenSnitch::autoMove(const Case grid[WIDTH][LENGTH]) {
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

string GoldenSnitch::getName() {
    return "G";
}

GoldenSnitch::operator JsonDict() const {
    JsonDict r;
    r.add("speed", new JsonInt(speed_));
    JsonList * position = new JsonList();
    position->add(new JsonInt(position_.x));
    position->add(new JsonInt(position_.y));
    r.add("position", position);
    return r;
}
