#include "Budger.h"

Budger::Budger():Ball(4) {
    srand (time(NULL));
}

Budger::~Budger(){ }

Position Budger::autoMove(const Case grid[WIDTH][LENGTH])
{
    Position nextPosition;
    int next = rand() % 6;
    nextPosition = nextCase(position_, next, grid);
    if(grid[nextPosition.x][nextPosition.y].type == USABLE){
        if(grid[nextPosition.x][nextPosition.y].ball == 0){
            return nextPosition;
        }
    }
    for(int i=0; i<5; i++){
        next = (next + 1)%6;
        nextPosition = nextCase(position_, next, grid);
        if(grid[nextPosition.x][nextPosition.y].type == USABLE){
            if(grid[nextPosition.x][nextPosition.y].ball == 0){
                return nextPosition;
            }
        }
    }
    return position_;

}

Way Budger::isHit(const char direction, const int power, const Case grid[WIDTH][LENGTH])
{
    Way way;
    for(int i =0; i<power; i++){
        way.push_back(nextCase(position_, direction, grid));
    }
    return way;
}

void Budger::hitPlayer(Player& player, int power)
{
    if (1 == rand() % 20)
        player.setWoundState(true);
}

std::string Budger::getName(){
    return "B";
}
