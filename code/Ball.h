#ifndef Ball_h
#define Ball_h

class Ball {

	public:
		virtual Ball();
		virtual ~Ball();
		virtual bool operator=(const Ball &ball)
		virtual void move();
		virtual int getSpeed();

	private:
		int speed;
};
#endif // Ball_h
