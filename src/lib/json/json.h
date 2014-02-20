#include <map>
#include <string>
#include <vector>

#define JDICT dynamic_cast<JsonDict*>
#define JLIST dynamic_cast<JsonList*>
#define JSTRING dynamic_cast<JsonString*>
#define JINT dynamic_cast<JsonInt*>

class JsonValue {
    public:
        static JsonValue * fromString(std::string message, int &i);
        static JsonValue * fromString(std::string message);

        virtual std::string toString() = 0;

    private:
        virtual void plop(){}
};


class JsonString : public JsonValue {
    public:
        JsonString(std::string val);

        static JsonString * fromString(std::string message, int &i);
        static JsonString * fromString(std::string message);

        std::string toString();

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

        std::string toString();

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

        std::string toString();

        JsonValue * operator[](const int &i);

        void add(JsonValue * value);
        size_t size();

    private:
        virtual void plop(){}
        std::vector<JsonValue *> content;
};

class JsonInt : public JsonValue {
    public:
        static JsonInt * fromString(std::string message, int &i);
        static JsonInt * fromString(std::string message);

        std::string toString();

        int getValue();
        void setValue(int val);
        void setValue(std::string val);

        operator std::string() const;
        operator int() const;

    private:
        virtual void plop(){}
        int value;
};
