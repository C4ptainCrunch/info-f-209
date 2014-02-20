#include <iostream>

#include "client.h"

using namespace std;


int main(int argc, char *argv[])
{
    if(argc <= 2){
        printf("Invalid parameters\nUsage : %s host port\n", argv[0]);
        exit(0);
    }
    int port = atoi(argv[2]);
    if(port <= 0 || port > 65535){
        printf("Invalid port\n");
        exit(0);
    }

    Client client(argv[1], port);

    client.run();

    return EXIT_SUCCESS;
}


Client::Client(char * host, int port)
{
    connectToServer(host, port);

    nextStateID_ = STATE_NULL;

    connected_ = false;
}

Client::~Client() {}

void Client::run()
{
    string buffer;
    currentStateID_ = STATE_INTRO;
    currentState_ = new IntroState(this);
    recv(buffer);
    if (buffer == "1")
        cout<<"Challenged !"<<endl;
    while(currentStateID_ != STATE_EXIT){
        currentState_->handleEvents();
        currentState_->logic();
        currentState_->display();

        changeState();
    }
}

void Client::connectToServer(char * host, const int port)
{
    int sockFd;
    struct timeval tv;

    tv.tv_sec = 2; //secondes de timeout
    tv.tv_usec = 0;
    if ((sockFd = socket(PF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Client: socket ");
        exit(EXIT_FAILURE);
    }

    setsockopt(sockFd, SOL_SOCKET, SO_RCVTIMEO, (char *)&tv,sizeof(struct timeval));

    socket_.setFd(sockFd);

    struct sockaddr_in theirAddr;
    struct hostent *he;

    socklen_t addrSize = sizeof(struct sockaddr);

    if ((he=gethostbyname(host)) == NULL) {
        cout << "Could not resolve hostname" << endl;
        exit(EXIT_FAILURE);
    }

    theirAddr.sin_family = AF_INET;
    theirAddr.sin_port = htons(port);
    theirAddr.sin_addr = *((struct in_addr*)he->h_addr);
    memset(&(theirAddr.sin_zero), '\0', 8);

    if (connect(socket_.getFd(), (struct sockaddr *)&theirAddr, addrSize) == -1) {
        perror("Connect");
        exit(EXIT_FAILURE);
    }
    connected_ = true;
}

void Client::disconnect()
{
    if (connected_) {
        connected_ = false;
        close(socket_.getFd());
    }
}

int Client::answerToChallenge(bool accept)
{
    return true;
}

int Client::send(const string & message)
{
    return socket_.write(message);
}

int Client::recv(string & message)
{
    return socket_.read(message);
}

void Client::setNextState(const int newStateID)
{
    if (nextStateID_ != STATE_EXIT)
        nextStateID_ = newStateID;
}

void Client::changeState()
{
    if (nextStateID_ != STATE_NULL){
        if (nextStateID_ != STATE_EXIT)
            delete currentState_;

        switch(nextStateID_){
            case STATE_INTRO:
                currentState_ = new IntroState(this);
                break;
            case STATE_MENU:
                currentState_ = new MenuState(this);
                break;
            case STATE_UNLOGGED:
                currentState_ = new UnloggedState(this);
                break;
            case STATE_MANAGE_PLAYERS:
                currentState_ = new ManagePlayerState(this);
                break;
            case STATE_MANAGE_INFRASTRUCTURES:
                currentState_ = new ManageInfrastructureState(this);
                break;
            case STATE_AUCTION_HOUSE:
                currentState_ = new AuctionHouseState(this);
                break;
            case STATE_CONNECTEDLIST:
                currentState_ = new ConnectedListState(this);
                break;
            case STATE_INGAME:
                currentState_ = new InGameState(this);
                break;
        }
        currentStateID_ = nextStateID_;
        nextStateID_ = STATE_NULL;
    }
}
