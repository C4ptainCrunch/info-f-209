#include "Installation.h"

Installation::Installation(int level) : level_(level){}

Installation::Installation(JsonValue * json) {
    JsonDict * installation = JDICT(json);

    if(installation == NULL)
        throw 1;

    JsonInt * level = JINT((*installation)["level"]);
    if(level == NULL)
        throw 1;

    Installation((int) *level);
}

Installation::~Installation(){}

void Installation::improve(){
    level_ += 1;
}

int Installation::getLevel(){
    return level_;
}
