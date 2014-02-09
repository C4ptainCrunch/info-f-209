#ifndef GAME_STATE_H
#define GAME_STATE_H

class GameState
{
public:
    virtual ~GameState();
    virtual void handleEvents() = 0;
    virtual void logic() = 0;
    virtual void display() = 0;

};

class IntroState : public GameState
{
public:
    virtual void handleEvents();
    virtual void logic();
    virtual void display();
};

class UnloggedState : public GameState
{
public:
    virtual void handleEvents();
    virtual void logic();
    virtual void display();
};

class MenuState : public GameState
{
public:
    virtual void handleEvents();
    virtual void logic();
    virtual void display();
};


class ManagePlayerState : public GameState
{
public:
    virtual void handleEvents();
    virtual void logic();
    virtual void display();
};

class ManageInfrastructureState : public GameState
{
public:
    virtual void handleEvents();
    virtual void logic();
    virtual void display();
};

class AuctionHouseState : public GameState
{
public:
    virtual void handleEvents();
    virtual void logic();
    virtual void display();
};

class InGameState : public GameState
{
public:
    virtual void handleEvents();
    virtual void logic();
    virtual void display();
};

#endif //GAME_STATE_H
