#ifndef JSON_H
#define JSON_H

#include <map>
#include <string>
#include <vector>

#include "utils.h"
#include "ParseError.h"
#include "ModelUnserialzationError.h"

#include <string>
#include <vector>
#include <iostream>
#include <typeinfo>
#include <map>

#define JDICT dynamic_cast<JsonDict*>
#define JLIST dynamic_cast<JsonList*>
#define JSTRING dynamic_cast<JsonString*>
#define JINT dynamic_cast<JsonInt*>
#define JNULL dynamic_cast<JsonNull*>
#define JBOOL dynamic_cast<JsonBool*>

class JsonValue {
    public:
        static JsonValue * fromString(std::string message, int &i);
        static JsonValue * fromString(std::string message);

        virtual std::string toString(){ return "";};

    private:
        virtual void plop(){}
};


class JsonString : public JsonValue {
    public:
        JsonString(std::string val);

        static JsonString * fromString(std::string message, int &i);
        static JsonString * fromString(std::string message);

        std::string toString();

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

        void add(std::string key, JsonValue * value);
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
        JsonInt(int val=0);

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

class JsonNull : public JsonValue {
    public:
        static JsonNull * fromString(std::string message, int &i);
        static JsonNull * fromString(std::string message);

        std::string toString();
        bool operator ==(const int * i);

    private:
        virtual void plop(){}
};

class JsonBool : public JsonValue {
    public:
        JsonBool(bool val);
        static JsonBool * fromString(std::string message, int &i);
        static JsonBool * fromString(std::string message);

        std::string toString();
        bool operator ==(const bool i);
        operator bool() const;
    private:
        virtual void plop(){}
        bool value;
};

#endif