#include "thread.h"

void connection(const int socket){
    Socket s(socket);
    std::string response = "";
    char buffer[RCV_SIZE];

    s.write("Hello, bite!");
    s.read(response);
    s.write(response);
    s.write("Bye");
    close(socket);

}