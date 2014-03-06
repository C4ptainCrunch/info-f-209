#include "Position.h"

bool operator==(const Position & pos1, const Position & pos2) {
    return (pos1.x == pos2.x) && (pos1.y == pos2.y);
}
