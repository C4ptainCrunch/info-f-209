#ifndef ITEM_H
#define ITEM_H

#include "../lib/json/json.h"

class Item{

    public:
        Item();
        Item(JsonValue * json);
        ~Item();
        operator JsonValue() const;
};

#endif // ITEM_H
