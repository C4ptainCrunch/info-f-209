#include <iostream>

#include "client.h"

using namespace std;


int main(int argc, char** argv)
{
    Client client;
    string message;

    if (argc != 2)
    {
        cout<<"Error : Enter argument"<<endl;
        return(EXIT_FAILURE); //rework here;
    }
    string name = argv[1];

    client.connectToName(name);

    while (message != "q" and message != "Q")
    {
        cout<<">>> ";
        cin>>message;
        client.send(message);
    }

    client.disconnect();

    return EXIT_SUCCESS;
}

Client::Client(){
    int sockFd;
    if ((sockFd = socket(PF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("Client: socket ");
        exit(EXIT_FAILURE);
    }

    socket_.setFd(sockFd);

    connected = false;

    cout<<"Client Initialised"<<endl;
}

void Client::connectToName(string name){

    struct sockaddr_in theirAddr;
    struct hostent *he;;

    if (connected)
    {
        cout<<"Already connected."<<endl; //Rework
    }
    else
    {
        socklen_t addrSize = sizeof(struct sockaddr);

        if ((he=gethostbyname(name.c_str())) == NULL)
        {
            perror("Client: gethostbyname ");
            exit(EXIT_FAILURE);
        }

        theirAddr.sin_family = AF_INET;
        theirAddr.sin_port = htons(PORT);
        theirAddr.sin_addr = *((struct in_addr*)he->h_addr);
        memset(&(theirAddr.sin_zero), '\0', 8);

        if (connect(socket_.getFd(), (struct sockaddr *)&theirAddr, addrSize) == -1)
        {
            perror("Client: connect ");
            exit(EXIT_FAILURE);
        }
        connected = true;
        printf("Connecté au serveur.");
    }
}

void Client::disconnect(){
    if (connected)
    {
        connected = false;
        close(socket_.getFd());
    }
    else
        cout<<"Disconnection : No connection"<<endl; //Rework
}

int Client::send(const string & message)
{
    return socket_.write(message);
}

int Client::recv(string & message)
{
    return socket_.read(message);
}
