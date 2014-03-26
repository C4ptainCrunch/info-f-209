#include "Quaffle.h"

using namespace std;

Quaffle::Quaffle(): Ball(0), thrownWay_() {}

Quaffle::Quaffle(int speed, Position position): Ball(speed, position) ,thrownWay_() {}

Quaffle::Quaffle(JsonValue * json) {

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

    new (this)Quaffle(speed, position);
}

Quaffle::~Quaffle() {}

void Quaffle::thrown(const char direction, const int power, const Case grid[WIDTH][LENGTH]) {
    Way way;
    for (int i = 0; i < power; i++) {
        way.push_back(nextCase(position_, direction, grid));
    }
    thrownWay_ = way;
}

string Quaffle::getName() {
    return "Q";
}

Way Quaffle::getWay() const {
    return thrownWay_;
}
