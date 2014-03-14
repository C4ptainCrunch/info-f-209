#include "views.h"

using namespace std;

void writeToServer(Socket * s, string topic, string message){
    s->write(topic + ":" + message);
}

namespace sviews {
void login(Socket * s, string username, string password){
    JsonDict answer;
    answer.add("username", new JsonString(username));
    answer.add("password", new JsonString(password));
    writeToServer(s, "login", answer.toString());
}

void signup(Socket * s, string username, string name, string password){
    JsonDict answer;
    answer.add("username", new JsonString(username));
    answer.add("name", new JsonString(name));
    answer.add("password", new JsonString(password));
    writeToServer(s, "register", answer.toString());
}

void userlist(Socket * s){
    writeToServer(s, "userlist", "True");
}

}