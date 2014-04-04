#include "views.h"

using namespace std;

void writeToServer(Socket * s, string topic, string message) {
    s->write(topic + ":" + message);
}

namespace sviews {
void login(Socket * s, string username, string password) {
    JsonDict answer;
    answer.add("username", new JsonString(username));
    answer.add("password", new JsonString(password));
    writeToServer(s, "login", answer.toString());
}

void signup(Socket * s, string username, string name, string password) {
    JsonDict answer;
    answer.add("username", new JsonString(username));
    answer.add("name", new JsonString(name));
    answer.add("password", new JsonString(password));
    writeToServer(s, "register", answer.toString());
}

void challenge(Socket * s, string opponent) {
    JsonDict answer;
    answer.add("other_username", new JsonString(opponent));
    writeToServer(s, "challenge", answer.toString());
}

void playerlist(Socket * s) {
    writeToServer(s, "playerlist", "true");
}

void userlist(Socket * s) {
    writeToServer(s, "userlist", "true");
}

void acceptChallenge(Socket * s, string opponent, int matchID) {
    JsonDict answer;
    answer.add("other_username", new JsonString(opponent));
    answer.add("id", new JsonInt(matchID));
    writeToServer(s, "accept_challenge", answer.toString());
}

void refuseChallenge(Socket * s, string opponent, int matchID) {
    JsonDict answer;
    answer.add("other_username", new JsonString(opponent));
    answer.add("id", new JsonInt(matchID));
    writeToServer(s, "refuse_challenge", answer.toString());
}

void endTurn(Socket * s, vector<Way> chosenWays) {
    JsonList message;
    for (int i = 0; i < chosenWays.size(); i++) {
        JsonList * way_list = new JsonList();
        for (int j = 0; j < chosenWays[i].size(); j++) {
            JsonList * pos_list = new JsonList();
            pos_list->add(new JsonInt(chosenWays[i][j].x));
            pos_list->add(new JsonInt(chosenWays[i][j].y));
            way_list->add(pos_list);
        }
        message.add(way_list);
    }
    writeToServer(s, "end_turn", message.toString());
}

void surrender(Socket * s) {
    writeToServer(s, "surrender", "true");
}

}
