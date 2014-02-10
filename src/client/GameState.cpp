#include <iostream>

#include "Socket.h"
#include "client.h"
#include "GameState.h"

#define STATUS_DEFAULT 0
#define STATUS_BAD_ENTRY -1
#define STATUS_DISCONNECT -2

#define CONNECTION_CONNECTED 1

#define MENU_MANAGEPLAYERS 1
#define MENU_MANAGEINFRASTRUCTURES 2
#define MENU_AUCTIONHOUSE 3
#define MENU_FRIENDLIST 4

using namespace std;

GameState::GameState(Client * client)
{
    client_ = client;
    status = STATUS_DEFAULT;
}

GameState::~GameState() {}

void GameState::setNextState(int state)
{
    client_->setNextState(state);
}


IntroState::IntroState(Client * client) : GameState(client)
{
    cout<<"BienvenuS dans le systme !"<<endl;
    setNextState(STATE_UNLOGGED);
}
void IntroState::handleEvents() {}
void IntroState::logic() {}
void IntroState::display() {}

//Unlogged-------------------------------------------------------------------------

UnloggedState::UnloggedState(Client * client) : GameState(client)
{
    cout<<"Entrez l'option souhaité avec les paramètres requis délimités par un espace."<<endl;
    cout<<"Par éxemple : '2 C4 gronoub'"<<endl;
    cout<<endl;
    display();
}
void UnloggedState::handleEvents()
{
    string entry;
    cin>>entry;
    //parse entry here
    //fill username and password here
}
void UnloggedState::logic()
{
    //send message to server here
    status = CONNECTION_CONNECTED;
    if (status == CONNECTION_CONNECTED)
        setNextState(STATE_MENU);
}
void UnloggedState::display()
{
    switch (status) {
    case STATUS_DEFAULT :
        cout<<"S'enregistrer : 1 - Nom d'utilisateur - Mot de passe"<<endl;
        cout<<"Se connecter : 2 - Nom d'utilisateur - Mot de passe"<<endl;
        cout<<endl;
        break;
    case CONNECTION_CONNECTED :
        cout<<"Connecté."<<endl;
        cout<<endl;
        break;
    case STATUS_BAD_ENTRY :
        cout<<"Erreur : votre entrée est incorrecte."<<endl;
        cout<<endl;
        break;
    }

}

//Menu-------------------------------------------------------------------------

MenuState::MenuState(Client * client) : GameState(client)
{
    display();
}
void MenuState::handleEvents()
{
    string entry;
    cin>>entry;
    //parse entry here
    status = MENU_MANAGEPLAYERS;
}
void MenuState::logic()
{
    switch (status) {
    case MENU_MANAGEPLAYERS :
        setNextState(STATE_EXIT);
        break;
    case MENU_MANAGEINFRASTRUCTURES :
        setNextState(STATE_EXIT);
        break;
    case MENU_AUCTIONHOUSE :
        setNextState(STATE_EXIT);
        break;
    case MENU_FRIENDLIST :
        setNextState(STATE_EXIT);
        break;
    }
}
void MenuState::display()
{
    switch (status) {
    case STATUS_DEFAULT :
        cout<<"Gérer votre équipe : 1"<<endl;
        cout<<"Gérer vos infrastructures : 2"<<endl;
        cout<<"Accéder à l'hotel de vente : 3"<<endl;
        cout<<"Voir la liste d'amis : 4"<<endl;
        cout<<"Se déconnecter : 5"<<endl;
        cout<<endl;
        break;
    case STATUS_BAD_ENTRY :
        cout<<"Erreur : votre entrée est incorrecte."<<endl;
        cout<<endl;
        break;
    }
}


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


//FriendList--------------------------------------------------------------------------

FriendListState::FriendListState(Client * client) : GameState(client) {}
void FriendListState::handleEvents() {}
void FriendListState::logic() {}
void FriendListState::display() {}


//InGame-------------------------------------------------------------------------

InGameState::InGameState(Client * client) : GameState(client) {}
void InGameState::handleEvents() {}
void InGameState::logic() {}
void InGameState::display() {}
