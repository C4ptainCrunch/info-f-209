#ifndef GAME_STATE_H
#define GAME_STATE_H

//Game States
enum GameStates
{
    STATE_NULL,
    STATE_EXIT,
    STATE_INTRO,

    STATE_UNLOGGED,
    STATE_MENU,
    STATE_MANAGE_PLAYERS,
    STATE_MANAGE_INFRASTRUCTURES,
    STATE_AUCTION_HOUSE,
    STATE_INGAME,
};

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
