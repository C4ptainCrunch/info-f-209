#include "Budger.h"

Budger::Budger():Ball(0) {
    srand (time(NULL));
} // TODO set speed

Budger::~Budger(){ }

Position Budger::autoMove(const Case grid[WIDTH][LENGHT])
{
    Position nextPosition;
    int next = rand() % 6;
    nextPosition = nextCase(position_, next);
    if(grid[nextPosition.x][nextPosition.y].type == USABLE){
        if(grid[nextPosition.x][nextPosition.y].ball == 0){
            return nextPosition;
        }
    }
    for(int i=0; i<5; i++){
        next = (next + 1)%6;
        nextPosition = nextCase(position_, next);
        if(grid[nextPosition.x][nextPosition.y].type == USABLE){
            if(grid[nextPosition.x][nextPosition.y].ball == 0){
                return nextPosition;
            }
        }
    }
    return position_;

}

Position Budger::isHit(const Position pos, const char direction, const int power)
{
    Position p = {1,1};
    return p;
}

void Budger::hitPlayer(Player& player, int power)
{
// TODO
}

