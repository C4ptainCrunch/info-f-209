#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <string>

class Client;

class GameState
{
public:
    GameState(Client * client);
    virtual ~GameState();
    virtual void handleEvents() = 0;
    virtual void logic() = 0;
    virtual void display() = 0;
protected:
    Client * client_;
    int status;
};

class IntroState : public GameState
{
public:
    IntroState(Client * client);
    virtual void handleEvents();
    virtual void logic();
    virtual void display();
};

class UnloggedState : public GameState
{
public:
    UnloggedState(Client * client);
    virtual void handleEvents();
    virtual void logic();
    virtual void display();
private:
    std::string nameEntry;
    std::string passEntry;
    int connectionStatus;
};

class MenuState : public GameState
{
public:
    MenuState(Client * client);
    virtual void handleEvents();
    virtual void logic();
    virtual void display();
};


class ManagePlayerState : public GameState
{
public:
    ManagePlayerState(Client * client);
    virtual void handleEvents();
    virtual void logic();
    virtual void display();
};

class ManageInfrastructureState : public GameState
{
public:
    ManageInfrastructureState(Client * client);
    virtual void handleEvents();
    virtual void logic();
    virtual void display();
};

class AuctionHouseState : public GameState
{
public:
    AuctionHouseState(Client * client);
    virtual void handleEvents();
    virtual void logic();
    virtual void display();
};

class InGameState : public GameState
{
public:
    InGameState(Client * client);
    virtual void handleEvents();
    virtual void logic();
    virtual void display();
};

#endif //GAME_STATE_H
