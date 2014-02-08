#include <iostream>

#include "client.h"

using namespace std;


int main(int argc, char** argv)
{
    int run = 1;
    string name;

    if (argc != 2)
    {
        fprintf(stderr, "Donnez le nom de la machine distante en argument.\n");
        return EXIT_FAILURE;
    }

    name = argv[1];

    Client client;
    client.connectToName(name);

    while (run == 1)
    {
        string message;

        cout<<"\n>>> ";
        cin>>message;

        client.stringToBuff(message);
        client.defaultSend();

        if (message == "q" or message == "Q")
        {
            printf("Fin de la connection.\n");
            run = 0;
        }
    }

    client.disconnect();
    return EXIT_SUCCESS;
}

Client::Client(){
    if ((sockFd = socket(PF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("Client: socket ");
        exit(EXIT_FAILURE);
    }

    connected = false;

    cout<<"Client Initialised"<<endl;
}

void Client::connectToName(string name){

    struct sockaddr_in theirAddr;
    struct hostent *he;
    socklen_t addrSize;

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

        if (connect(sockFd, (struct sockaddr *)&theirAddr, addrSize) == -1)
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
        close(sockFd);
    }
    else
        cout<<"Disconnection : No connection"<<endl; //Rework
}

void Client::stringToBuff(string message){
    strncpy(buffer, message.c_str(), BUFFERSIZE);
}

int Client::defaultRecv()
{
    if (connected)
    {
        int numbytes;

        if ((numbytes = recv(sockFd, buffer, BUFFERSIZE, 0)) == -1)
        {
            char errorText[50];
            sprintf(errorText, "Client : recv ");
            perror(errorText);
            exit(EXIT_FAILURE);
        }

        return numbytes;
    }

    else
        cout<<"Recv : No connection"<<endl; //Rework
}

int Client::defaultSend()
{
    if (connected)
    {
        int res;

        if ((res = send(sockFd, buffer, BUFFERSIZE, 0)) == -1)
        {
            char errorText[50];
            sprintf(errorText, "Client : send ");
            perror(errorText);
            exit(EXIT_FAILURE);
        }

        return res;
    }

    else
        cout<<"Send : No connection"<<endl; //Rework
}
