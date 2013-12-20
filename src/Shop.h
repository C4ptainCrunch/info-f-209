#ifndef Shop_h
#define Shop_h

#include "Installation.h"


class Shop : protected Installation {

	public:
		virtual Shop();
		virtual ~Shop();
		virtual Shop operator=();
		virtual void improve();
		virtual int getLevel();
		virtual int getIncome();
		virtual void setIncome();

	protected:
		int income;
};

#endif // Shop_h
