#ifndef ITEM_H
#define ITEM_H

#include "../lib/json/json.h"
#include "ModelUnserializationError.h"

class Item {

public:
    Item();
    Item(JsonValue * json);
    ~Item();
    operator JsonDict() const;
};

#endif // ITEM_H
