#include "serverhandler.h"

using namespace std;


const map<string, view_ptr> ServerHandler::viewmap = {
    {"login", rviews::login},
    {"register", rviews::signup},
    {"userlist", rviews::userlist}
};

ServerHandler::ServerHandler(string host, const int port, MainWindow * window) {
    host_ = host;
    port_ = port;
    s_ = NULL;
    window_ = window;
}

ServerHandler::~ServerHandler() {
    if(s_ != NULL){
        delete s_;
    }
}

bool ServerHandler::connect_socket(){
    int sockFd;

    if ((sockFd = socket(PF_INET, SOCK_STREAM, 0)) == -1) {
        // perror("Client: socket ");
        return false;
    }

    s_ = new Socket(sockFd);

    struct sockaddr_in theirAddr;
    struct hostent * he;

    socklen_t addrSize = sizeof(struct sockaddr);

    if ((he = gethostbyname(host_.c_str())) == NULL) {
        // cout << "Could not resolve hostname" << endl;
        return false;
    }

    theirAddr.sin_family = AF_INET;
    theirAddr.sin_port = htons(port_);
    theirAddr.sin_addr = *((struct in_addr *)he->h_addr);
    memset(&(theirAddr.sin_zero), '\0', 8);

    if (connect(s_->getFd(), (struct sockaddr *)&theirAddr, addrSize) == -1) {
        // perror("Connect");
        return false;
    }

    window_->setSocket(s_);

    return true;
}

void ServerHandler::send(string message){
    if(s_ == NULL){
        throw 1;
    }
    s_->write(message);
}

int ServerHandler::recieve(string & message){
    if(s_ == NULL){
        throw 1;
    }
    return s_->read(message);
}

void ServerHandler::handleMessage(string message) {
    string key;

    message = split_message(&key, message);
    try {
        try {
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

