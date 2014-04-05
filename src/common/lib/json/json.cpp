#include "json.h"

using namespace std;

// Value

JsonValue * JsonValue::fromString(string message) {
    int i = 0;
    return JsonValue::fromString(message, i);
}


JsonValue * JsonValue::fromString(string message, int & i) {
    while (i < message.length()) {
        i += skip_whitespace(message, i);
        switch (message[i]) {
            case '{':
                return JsonDict::fromString(message, i);
                break;
            case '[':
                return JsonList::fromString(message, i);
                break;
            case '"':
                return JsonString::fromString(message, i);
                break;
            case 't':
            case 'f':
                return JsonBool::fromString(message, i);
            case 'n':
                return JsonNull::fromString(message, i);
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                return JsonInt::fromString(message, i);
                break;
            default:
                throw PARSE_ERROR("unknwown value. Got '" + string(1, message[i]) + "'", i);
        }
    }
    throw PARSE_ERROR("no value found", i);
}


// String

JsonString::JsonString(string val) {
    replace_all(val, "\\\\", '\\');
    replace_all(val, "\\\"", '"');
    replace_all(val, "\\t", '\t');
    replace_all(val, "\\n", '\n');
    replace_all(val, "\\r", '\r');
    replace_all(val, "\\b", '\b');
    replace_all(val, "\\f", '\f');
    // TODO : replace \u four-hex-digits
    value = val;
}

JsonString::operator string() const {
    return value;
}


JsonString * JsonString::fromString(string message, int & i) {
    i++;
    int start = i;
    while (i < message.length()) {
        switch (message[i]) {
            case '\\':
                i++;
                break;
            case '"':
                string s = message.substr(start, i - start);
                i++;
                return new JsonString(s);
        }
        i++;
    }
    throw PARSE_ERROR("No \" ending string", i);
}

string JsonString::toString() {
    string infos = "\"" + this->value + "\"";
    return infos;
}

// Dict

JsonDict::~JsonDict() {
    for (std::map<std::string, JsonValue *>::iterator iter = dict.begin(); iter != dict.end(); ++iter) {
        delete iter->second;
        iter->second = NULL;
    }
}

JsonDict * JsonDict::fromString(string message, int & i) {
    i++;
    JsonDict * r = new JsonDict();
    i += skip_whitespace(message, i);

    if (message[i] == '}') {
        i++;
        return r;
    }

    while (1) {
        JsonString * key = NULL;
        JsonValue * value = NULL;

        i += skip_whitespace(message, i);
        key = JsonString::fromString(message, i);
        string key_str = *key;
        delete key;
        i += skip_whitespace(message, i);
        i += skip_colon(message, i);
        i += skip_whitespace(message, i);
        value = JsonValue::fromString(message, i);
        r->add(key_str, value);

        i += skip_whitespace(message, i);
        if (message[i] == ',') {
            i++;
        }
        else if (message[i] == '}') {
            i++;
            return r;
        }
        else {
            throw PARSE_ERROR("expected } or , found '" + string(1, message[i]) + "'", i);
        }
    }
}

string JsonDict::toString() {
    string infos = "{";
    for (map<string, JsonValue *>::iterator index = this->dict.begin(); index != this->dict.end(); ++index) {
        infos += "\"" + ((string) index->first) + "\"" + " : ";
        infos += index->second->toString();
        infos += ", ";
    }
    infos = infos.substr(0, infos.size() - 2) + "}";
    return infos;
}

void JsonDict::add(string key, JsonValue * value) {
    dict[key] = value;
}

size_t JsonDict::size() {
    return dict.size();
}

JsonValue * JsonDict::operator[](const string & str) {
    return this->dict[str];
}


// List

JsonList::~JsonList() {
    for (int i = 0; i < content.size(); i++) {
        delete content[i];
        content[i] = NULL;
    }
}

JsonList * JsonList::fromString(string message, int & i) {
    i++;
    JsonList * r = new JsonList();
    i += skip_whitespace(message, i);

    if (message[i] == ']') {
        i++;
        return r;
    }

    while (1) {
        JsonValue * value = NULL;

        i += skip_whitespace(message, i);
        value = JsonValue::fromString(message, i);
        r->add(value);

        i += skip_whitespace(message, i);

        switch (message[i]) {
            case ',':
                i++;
                break;
            case ']':
                i++;
                return r;
                break;
            default:
                throw PARSE_ERROR("expected ] or , found " + string(1, message[i]), i);
        }
    }
}

string JsonList::toString() {
    string infos = "[";
    int index = 0;
    while (index < this->content.size()) {
        infos += this->content[index]->toString();
        index++;
        infos += ", ";
    }

    infos = infos.substr(0, infos.size() - 2) + "]";
    return infos;
}

void JsonList::add(JsonValue * value) {
    content.push_back(value);
}

size_t JsonList::size() {
    return content.size();
}

JsonValue * JsonList::operator[](const int & i) {
    return content.at(i);
}


// Int

JsonInt::JsonInt(int val) {
    value = val;
}

JsonInt * JsonInt::fromString(string message, int & i) {
    JsonInt * r = new JsonInt();
    bool end = false;
    int start = i;
    while (!end) {
        switch (message[i]) {
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                i++;
                break;
            default:
                end = true;
                break;
        }
    }
    r->setValue(message.substr(start, i));
    return r;
}

string JsonInt::toString() {
    return (string) * this;
}


int JsonInt::getValue() {
    return value;
}

void JsonInt::setValue(int val) {
    value = val;
}

void JsonInt::setValue(string val) {
    try {
        value = stoi(val);
    }
    catch (out_of_range) {
        throw ParseError("Int too big to be parsed");
    }
}

JsonInt::operator string() const {
    return to_string(value);
}

JsonInt::operator int() const {
    return value;
}

// Null

string JsonNull::toString() {
    return "null";
}

JsonNull * JsonNull::fromString(string message, int & i) {
    if (message.substr(i, 4) != "null") {
        throw PARSE_ERROR("expected null, got '" + message.substr(i, 4) + "'", i);
    }
    i += 4;
    return new JsonNull();
}

bool JsonNull::operator ==(const int * i) {
    return i == 0;
}

// Bool

JsonBool::JsonBool(bool val) {
    value = val;
}

JsonBool * JsonBool::fromString(string message, int & i) {
    JsonBool * r = NULL;
    if (message[i] == 't') {
        if (message.substr(i, 4) != "true") {
            throw PARSE_ERROR("expected true, got '" + message.substr(i, 4) + "'", i);
        }
        r = new JsonBool(true);
        i += 4;
    }
    else {
        if (message.substr(i, 5) != "false") {
            throw PARSE_ERROR("expected false, got '" + message.substr(i, 5) + "'", i);
        }
        r = new JsonBool(false);
        i += 5;
    }

    return r;
}

string JsonBool::toString() {
    if (value) {
        return "true";
    }
    else {
        return "false";
    }
}

bool JsonBool::operator ==(const bool i) {
    return value == i;
}

JsonBool::operator bool() const {
    return value;
}
