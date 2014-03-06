#include "Quaffle.h"

using namespace std;

Quaffle::Quaffle(): Ball(0) { }

Quaffle::~Quaffle() { }

Way Quaffle::thrown(const char direction, const int power, const Case grid[WIDTH][LENGTH])
{
    Way way;
    for(int i =0; i<power; i++){
        way.push_back(nextCase(position_, direction, grid));
    }
    return way;
}

string Quaffle::getName(){
    return "Q";
}
