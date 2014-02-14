#include <map>
#include <string>
#include <vector>

class JsonValue {
    public:
        virtual void plop(){}
};

class JsonString : public JsonValue {
    public:
        JsonString();
        JsonString operator=(const JsonString &str);
        operator std::string() const;
        JsonString(std::string val);
        std::string value;
        void plop(){}
};

class JsonDict : public JsonValue {
    public:
        JsonDict();
        void add(JsonString key, JsonValue * value);
        std::map<std::string, JsonValue *> dict;
        void plop(){}
};

class JsonList : public JsonValue {
    public:
        JsonList();
        void add(JsonValue * value);
        std::vector<JsonValue *>content;
        void plop(){}
};

JsonString * createString(std::string message, int &i);
JsonDict * createDict(std::string message, int &i);
JsonValue * createValue(std::string message, int &i);
JsonValue * createNumber(std::string message, int &i);
JsonList * createList(std::string message, int &i);