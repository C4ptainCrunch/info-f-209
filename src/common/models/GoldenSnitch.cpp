#include "GoldenSnitch.h"

using namespace std;

GoldenSnitch::GoldenSnitch(): Ball(42) {
    srand(time(NULL));
}

GoldenSnitch::GoldenSnitch(int speed, Position position): Ball(speed, position){ }

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
