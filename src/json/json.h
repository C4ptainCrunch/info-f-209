#include <map>
#include <string>

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

JsonString * createString(std::string message, int &i);
JsonDict * createDict(std::string message, int &i);
JsonValue * createValue(std::string message, int &i);
JsonValue * createNumber(std::string message, int &i);
JsonValue * createList(std::string message, int &i);