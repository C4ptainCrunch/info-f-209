#include "Item.h"

Item::Item(){}

Item::Item(JsonValue * json){
    JsonDict * item_dict = JDICT(json);
    if(item_dict == NULL)
        throw 1;
}

Item::~Item(){}