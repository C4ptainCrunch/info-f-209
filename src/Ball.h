#ifndef BALL_H
#define BALL_H

class Ball {

    public:
        Ball();
        ~Ball();
        virtual void move();
        virtual int getSpeed();
        virtual void setSpeed();

    protected:
        int speed;
};
#endif // BALL_H
