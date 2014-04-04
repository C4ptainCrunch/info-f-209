#include "serverhandler.h"

using namespace std;


const map<string, view_ptr> ServerHandler::viewmap = {
    {"login", rviews::login},
    {"register", rviews::signup},
    {"userlist", rviews::userlist},
    {"playerlist", rviews::playerlist},
    {"startMatch", rviews::startMatch},
    {"challenge", rviews::challenge},
    {"end_match", rviews::endMatch},
    {"updateMatch", rviews::updateMatch}
};

ServerHandler::ServerHandler(string host, const int port, MainWindow * window) {
    host_ = host;
    port_ = port;
    s_ = NULL;
    window_ = window;
}

ServerHandler::~ServerHandler() {
    if (s_ != NULL) {
        delete s_;
    }
}

bool ServerHandler::connect_socket() {
    try {
        s_ = new Socket(host_, port_);
    }
    catch (...) {
        return false;
    }
    window_->setSocket(s_);
    return true;
}

void ServerHandler::send(string message) {
    if (s_ == NULL) {
        throw 1;
    }
    s_->write(message);
}

int ServerHandler::recieve(string & message) {
    if (s_ == NULL) {
        throw 1;
    }
    return s_->read(message);
}

void ServerHandler::handleMessage(string message) {
    string key;

    message = split_message(&key, message);
    try {
        try {
            cout<<key<<endl;
            ServerHandler::viewmap.at (key)(JsonValue::fromString(message), this);
        }
        catch (const std::out_of_range & oor) {
            cout << "Unknown topic : '" + key + "'" << endl;
        }
    }
    catch (const BadRequest & br) {
        cout << "Bad request : " <<  br.what() << endl;
    }
    catch (const ParseError & pe) {
        cout << "Parse error : " <<  pe.what() << endl;
    }
}

int ServerHandler::loop() {
    string message;
    while (1) {
        if (s_->read(message) != 1) {
            return 0;
        }
        handleMessage(message);
    }
}

MainWindow * ServerHandler::getWindow() {
    return window_;
}

string split_message(string * key, string message) {
    size_t found = message.find(':');
    *key = message.substr(0, found);
    return message.substr(found + 1, message.length());
}
