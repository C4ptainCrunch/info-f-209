Position nextCase(Position position, int direction){
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
            nextPosition--;
            if(position.x % 2 != 2)
                nextPosition.y--;
            break;
    }
    return nextPosition;
}

