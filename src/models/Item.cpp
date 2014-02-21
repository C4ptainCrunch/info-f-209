#include "Item.h"

Item::Item(){}

Item::Item(JsonValue * json){
    JsonDict * item_dict = JDICT(json);
    if(item_dict == NULL)
        throw ModelUnserialzationError();
}

Item::~Item(){}

Item::operator JsonValue() const{
    JsonDict r;
    return r;
}