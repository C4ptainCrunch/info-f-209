#include <map>
#include <string>
#include <vector>

class JsonValue {
    public:
        static JsonValue * fromString(std::string message, int &i);
        static JsonValue * fromString(std::string message);

    private:
        virtual void plop(){}
};


class JsonString : public JsonValue {
    public:
        JsonString(std::string val);

        static JsonString * fromString(std::string message, int &i);
        static JsonString * fromString(std::string message);

        JsonString operator=(const JsonString &str);
        operator std::string() const;

    private:
        virtual void plop(){}
        std::string value;
};

class JsonDict : public JsonValue {
    public:
        static JsonDict * fromString(std::string message, int &i);
        static JsonDict * fromString(std::string message);

        JsonValue * operator[](const std::string &str);

        void add(JsonString key, JsonValue * value);
        size_t size();

    private:
        virtual void plop(){}
        std::map<std::string, JsonValue *> dict;
};

class JsonList : public JsonValue {
    public:
        static JsonList * fromString(std::string message, int &i);
        static JsonList * fromString(std::string message);

        JsonValue * operator[](const int &i);

        void add(JsonValue * value);
        size_t size();

    private:
        virtual void plop(){}
        std::vector<JsonValue *>content;
};

JsonValue * createNumber(std::string message, int &i);