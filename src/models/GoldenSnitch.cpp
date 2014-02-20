#include "GoldenSnitch.h"

GoldenSnitch::GoldenSnitch():Ball(0) { 
    srand (time(NULL));
} //TODO set speed

GoldenSnitch::~GoldenSnitch(){ }

Position GoldenSnitch::autoMove(const Case& grid[WIDTH][LENGTH])
{
    Position nextPosition;
    next = rand() % 6;
    nextPosition = nextCase(position_, next);
    if(grid[nextPosition][nextPosition].type == USABLE){
        if(grid[nextPosition][nextPosition].ball == 0){
            return nextPosition;
        }
    }
    for(int i=0; i<5; i++){
        next = (next + 1)%6
        nextPosition = nextCase(position_, next);
        if(grid[nextPosition][nextPosition].type == USABLE){
            if(grid[nextPosition][nextPosition].ball == 0){
                return nextPosition;
            }
        }
    }
    return position_;
}
