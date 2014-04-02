#include "Case.h"
using namespace std;



Case Case::fromJson(JsonValue * json){
    JsonDict * case_dict = JDICT(json);
    if (case_dict == NULL) {
        throw ModelUnserializationError(string(__FUNCTION__) + " in " + string(__FILE__) + ":" + to_string(__LINE__));
    }

    JsonInt * type_int = JINT((*case_dict)["type"]);
    if (type_int == NULL) {
        throw ModelUnserializationError(string(__FUNCTION__) + " in " + string(__FILE__) + ":" + to_string(__LINE__));
    }

    int type = *type_int;

    FieldPlayer * player = new FieldPlayer((*case_dict)["player"]);

    Case newCase;
    newCase.type = type;
    newCase.player = player;
    newCase.ball = 0;
    return newCase;

}

Case::operator JsonDict() const {
    JsonDict r;
    r.add("type", new JsonInt(type));
    r.add("player", new JsonDict(*player));
    return r;
}

bool isCloseCase(Position position1, Position position2, const Case grid[WIDTH][LENGTH]){
    for (int i = 0; i<6; ++i){
        if (position2 == nextCase(position1,i,grid)){
            return true;
        }
    }
    return false;
}

Position nextCase(Position position, int direction, const Case grid[WIDTH][LENGTH]) {
    Position nextPosition;
    nextPosition.x = position.x;
    nextPosition.y = position.y;
    switch (direction) {
        case UP_RIGHT:
            nextPosition.x--;
            if (position.x % 2  == 0) {
                nextPosition.y++;
            }
            break;
        case RIGHT:
            nextPosition.y++;
            break;
        case DOWN_RIGHT:
            nextPosition.x++;
            if (position.x % 2 == 0) {
                nextPosition.y++;
            }
            break;
        case DOWN_LEFT:
            nextPosition.x++;
            if (position.x % 2 != 0) {
                nextPosition.y--;
            }
            break;
        case LEFT:
            nextPosition.y--;
            break;
        case UP_LEFT:
            nextPosition.x--;
            if (position.x % 2 != 2) {
                nextPosition.y--;
            }
            break;
    }
    if (grid[nextPosition.x][nextPosition.y].type == VOID) {
        nextPosition.x = position.x;
        nextPosition.y = position.y;
    }
    return nextPosition;
}
