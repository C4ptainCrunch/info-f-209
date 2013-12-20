#ifndef Ball_h
#define Ball_h

class Ball {

	public:
		virtual Ball();
		virtual ~Ball();
		virtual Ball operator=();
		virtual void move();
		virtual int getSpeed();
		virtual void setSpeed();

	private:
		int speed;
};
#endif // Ball_h
