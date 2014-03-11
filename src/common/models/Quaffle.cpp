#include "Quaffle.h"

using namespace std;

Quaffle::Quaffle(): Ball(0), thrownWay() {}

Quaffle::~Quaffle() {}

void Quaffle::thrown(const char direction, const int power, const Case grid[WIDTH][LENGTH]) {
    Way way;
    for (int i = 0; i < power; i++) {
        way.push_back(nextCase(position_, direction, grid));
    }
    thrownWay = way;
}

string Quaffle::getName() {
    return "Q";
}

Way Quaffle::getWay() const{
    return thrownWay;
}
