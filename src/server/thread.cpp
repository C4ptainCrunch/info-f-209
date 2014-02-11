#include "thread.h"

void connection(const int socket){
    Socket s(socket);
    std::string response = "";
    char buffer[RCV_SIZE];

    sendTo(socket, "Hello, bite!");
    s.read(response);
    sendTo(socket, response);
    sendTo(socket, "Bye");
    close(socket);

}