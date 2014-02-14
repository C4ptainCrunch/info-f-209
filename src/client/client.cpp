#include <iostream>

#include "client.h"

using namespace std;


int main()
{
    Client client;

    client.run();

    return EXIT_SUCCESS;
}

void Client::run()
{
    currentStateID_ = STATE_INTRO;
    currentState_ = new IntroState(this);

    while(currentStateID_ != STATE_EXIT){
        currentState_->handleEvents();
        currentState_->logic();
        currentState_->display();

        changeState();
    }
}

Client::Client()
{
    int sockFd;
    if ((sockFd = socket(PF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Client: socket ");
        exit(EXIT_FAILURE);
    }

    socket_.setFd(sockFd);

    nextStateID_ = STATE_NULL;

    connected_ = false;
}

Client::~Client() {}

void Client::connectToName(const string name)
{
    struct sockaddr_in theirAddr;
    struct hostent *he;;

    if (connected_)
        cout<<"Erreur : Déjà connecté."<<endl; //Rework. Throw exception?

    else {
        socklen_t addrSize = sizeof(struct sockaddr);

        if ((he=gethostbyname(name.c_str())) == NULL) {
            perror("Client: gethostbyname ");
            exit(EXIT_FAILURE);
        }

        theirAddr.sin_family = AF_INET;
        theirAddr.sin_port = htons(PORT);
        theirAddr.sin_addr = *((struct in_addr*)he->h_addr);
        memset(&(theirAddr.sin_zero), '\0', 8);

        if (connect(socket_.getFd(), (struct sockaddr *)&theirAddr, addrSize) == -1) {
            perror("Client: connect ");
            exit(EXIT_FAILURE);
        }
        connected_ = true;
        printf("Connecté au serveur."); //Rework. Server should mssg?
    }
}

void Client::disconnect()
{
    if (connected_) {
        connected_ = false;
        close(socket_.getFd());
    }
    else
        cout<<"Erreur : Non connecté lors d'une demande de déconnection."<<endl; //Rework. throw?
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
