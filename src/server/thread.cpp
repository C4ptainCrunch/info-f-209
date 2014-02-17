#include "thread.h"

#include <iostream>

using namespace std;

void connection(const int socket){
    Socket s(socket);
    std::string response = "";
    char buffer[RCV_SIZE];

    s.write("Hello, ULB!");
    s.read(response);
    s.write(response);
    s.read(response);
    s.write(response);
    s.write("Bye :)");
    close(socket);

}