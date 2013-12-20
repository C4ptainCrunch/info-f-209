#ifndef Shop_h
#define Shop_h

#include "Installation.h"


class Shop : protected Installation {

	public:
		virtual Shop();
		virtual ~Shop();
		virtual bool operator=();
		virtual void improve();
		virtual int getLevel();
		virtual int getIncome();
		virtual void setIncome();

	private:
		super();
		int income;
};

#endif // Shop_h
