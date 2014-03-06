#include "Infirmary.h"

Infirmary::Infirmary(int level): Installation(level) {}

Infirmary::~Infirmary() {}

void Infirmary::heal(Player & player) {
    player.setWoundedState(false);
}
