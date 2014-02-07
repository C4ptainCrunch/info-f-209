#define RCV_SIZE 2

void connection(const int socket){
    std::string response = "";
    char buffer[RCV_SIZE];

    sendTo(socket, "Hello, bite!");
    response = recieveFrom(socket, buffer);
    sendTo(socket, response);
    sendTo(socket, "Bye");
    close(socket);

}