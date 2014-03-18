#include "Item.h"

using namespace std;

Item::Item() {}

Item::Item(JsonValue * json) {
    JsonDict * item_dict = JDICT(json);
    if (item_dict == NULL) {
        throw ModelUnserializationError("Item initialized from non dict");
    }
}

Item::~Item() {}

Item::operator JsonDict() const {
    JsonDict r;
    return r;
}
