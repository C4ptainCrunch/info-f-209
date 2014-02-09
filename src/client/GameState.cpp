#include <iostream>

#include "Socket.h"
#include "client.h"
#include "GameState.h"

using namespace std;

GameState::GameState(Client * client)
{
    client_ = client;
}

GameState::~GameState() {}

IntroState::IntroState(Client * client) : GameState(client) {}
void IntroState::handleEvents()
{
    string message;
    cout<<"Type in 'stop'"<<endl;
    cin>>message;
    cout<<message<<endl;
    if (message == "stop")
        client_->setNextState(STATE_EXIT);
}
void IntroState::logic() {}
void IntroState::display() {}

UnloggedState::UnloggedState(Client * client) : GameState(client) {}
void UnloggedState::handleEvents() {}
void UnloggedState::logic() {}
void UnloggedState::display() {}

MenuState::MenuState(Client * client) : GameState(client) {}
void MenuState::handleEvents() {}
void MenuState::logic() {}
void MenuState::display() {}

ManagePlayerState::ManagePlayerState(Client * client) : GameState(client) {}
void ManagePlayerState::handleEvents() {}
void ManagePlayerState::logic() {}
void ManagePlayerState::display() {}

ManageInfrastructureState::ManageInfrastructureState(Client * client) : GameState(client) {}
void ManageInfrastructureState::handleEvents() {}
void ManageInfrastructureState::logic() {}
void ManageInfrastructureState::display() {}

AuctionHouseState::AuctionHouseState(Client * client) : GameState(client) {}
void AuctionHouseState::handleEvents() {}
void AuctionHouseState::logic() {}
void AuctionHouseState::display() {}

InGameState::InGameState(Client * client) : GameState(client) {}
void InGameState::handleEvents() {}
void InGameState::logic() {}
void InGameState::display() {}
