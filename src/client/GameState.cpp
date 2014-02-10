#include <iostream>

#include "Socket.h"
#include "client.h"
#include "GameState.h"

#define DEFAULT 0

#define CONNECTED 1

using namespace std;

GameState::GameState(Client * client)
{
    client_ = client;
}

GameState::~GameState() {}

IntroState::IntroState(Client * client) : GameState(client)
{
    cout<<"BienvenuS dans le systme !"<<endl;
    client_->setNextState(STATE_UNLOGGED);
}
void IntroState::handleEvents() {}
void IntroState::logic() {}
void IntroState::display() {}

//Unlogged-------------------------------------------------------------------------

UnloggedState::UnloggedState(Client * client) : GameState(client)
{
    connectionStatus = 0;
    cout<<"Entrez l'option souhaité avec les paramètres requis délimités par un espace."<<endl;
    cout<<"Par éxemple : '2 C4 gronoub'"<<endl<<endl;
    display();
}
void UnloggedState::handleEvents()
{
    string entry;
    cin>>entry;
    //parse entry here
}
void UnloggedState::logic()
{
    connectionStatus = CONNECTED;
    if (connectionStatus == CONNECTED)
        client_->setNextState(STATE_MENU);
}
void UnloggedState::display()
{
    if (connectionStatus == CONNECTED)
        cout<<"Connecté."<<endl;
    else
    {
    cout<<"S'enregistrer : 1 - Nom d'utilisateur - Mot de passe"<<endl;
    cout<<"Se connecter : 2 - Nom d'utilisateur - Mot de passe"<<endl<<endl;
    }
}

//Menu-------------------------------------------------------------------------

MenuState::MenuState(Client * client) : GameState(client)
{
    cout<<"Hello"<<endl;
    client_->setNextState(STATE_EXIT);
}
void MenuState::handleEvents() {}
void MenuState::logic() {}
void MenuState::display() {}


//ManagePlayer-------------------------------------------------------------------------

ManagePlayerState::ManagePlayerState(Client * client) : GameState(client) {}
void ManagePlayerState::handleEvents() {}
void ManagePlayerState::logic() {}
void ManagePlayerState::display() {}


//ManageInfrastructure-------------------------------------------------------------------------

ManageInfrastructureState::ManageInfrastructureState(Client * client) : GameState(client) {}
void ManageInfrastructureState::handleEvents() {}
void ManageInfrastructureState::logic() {}
void ManageInfrastructureState::display() {}


//AuctionHouse-------------------------------------------------------------------------

AuctionHouseState::AuctionHouseState(Client * client) : GameState(client) {}
void AuctionHouseState::handleEvents() {}
void AuctionHouseState::logic() {}
void AuctionHouseState::display() {}


//InGame-------------------------------------------------------------------------

InGameState::InGameState(Client * client) : GameState(client) {}
void InGameState::handleEvents() {}
void InGameState::logic() {}
void InGameState::display() {}
