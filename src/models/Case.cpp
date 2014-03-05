#include "Case.h"

Position nextCase(Position position, int direction, const Case grid[WIDTH][LENGHT]){
    Position nextPosition;
    nextPosition.x = position.x;
    nextPosition.y = position.y;
    switch (direction){
        case UP_RIGHT:
            nextPosition.x--;
            if(position.x % 2  == 0)
                nextPosition.y++;
            break;
        case RIGHT:
            nextPosition.y++;
            break;
        case DOWN_RIGHT:
            nextPosition.x++;
            if(position.x % 2 == 0)
                nextPosition.y++;
            break;
        case DOWN_LEFT:
            nextPosition.x++;
            if(position.x % 2 !=0)
                nextPosition.y--;
            break;
        case LEFT:
            nextPosition.y--;
            break;
        case UP_LEFT:
            nextPosition.x--;
            if(position.x % 2 != 2)
                nextPosition.y--;
            break;
    }
    if(grid[nextPosition.x][nextPosition.y].type == VOID){
        nextPosition.x = position.x;
        nextPosition.y = position.y;
    }
    return nextPosition;
}
