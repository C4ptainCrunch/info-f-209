#include <iostream>

#include "Socket.h"

#include "GameState.h"

using namespace std;

GameState::~GameState() {}

void IntroState::handleEvents() {}
void IntroState::logic() {}
void IntroState::display() {}

void UnloggedState::handleEvents() {}
void UnloggedState::logic() {}
void UnloggedState::display() {}

void MenuState::handleEvents() {}
void MenuState::logic() {}
void MenuState::display() {}

void ManagePlayerState::handleEvents() {}
void ManagePlayerState::logic() {}
void ManagePlayerState::display() {}

void ManageInfrastructureState::handleEvents() {}
void ManageInfrastructureState::logic() {}
void ManageInfrastructureState::display() {}

void AuctionHouseState::handleEvents() {}
void AuctionHouseState::logic() {}
void AuctionHouseState::display() {}

void InGameState::handleEvents() {}
void InGameState::logic() {}
void InGameState::display() {}
