#ifndef BALL_H
#define BALL_H

class Ball {

    public:
        Ball(int speed);
        virtual ~Ball();

    protected:
        int speed_;
};
#endif // BALL_H