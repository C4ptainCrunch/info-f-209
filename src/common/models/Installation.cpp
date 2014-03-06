#include "Installation.h"

Installation::Installation(int level): level_(level) {}

Installation::Installation(JsonValue * json) {
    JsonDict * installation = JDICT(json);

    if (installation == NULL) {
        throw ModelUnserializationError();
    }

    JsonInt * level = JINT((*installation)["level"]);
    if (level == NULL) {
        throw ModelUnserializationError();
    }

    Installation((int) *level);
}

Installation::~Installation() {}

void Installation::improve() {
    level_ += 1;
}

int Installation::improvePrice() {
    return baseprice_ + pow(powerprice_, level_);
}

int Installation::getLevel() {
    return level_;
}

Installation::operator JsonValue() const {
    JsonDict r;

    r.add("level", new JsonInt(level_));

    return r;
}
