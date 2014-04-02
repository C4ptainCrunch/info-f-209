#ifndef QUAFFLE_H
#define QUAFFLE_H

#include <string>

#include "Position.h"
#include "Case.h"

#include "Ball.h"

class Quaffle: public Ball {

public:
    Quaffle();
    Quaffle(JsonValue * json);
    Quaffle(int speed, Position position);
    ~Quaffle();
    operator JsonDict() const;
    void thrown(const char direction, const int power, const Case grid[WIDTH][LENGTH]);
    std::string getName();
    Way getWay() const;

private:
    Way thrownWay_;
};

#endif // QUAFFLE_H
