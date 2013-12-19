#ifndef Shop_h
#define Shop_h

#include "Installation.h"


class Shop : protected Installation {

	public:
		virtual Shop();
		virtual ~Shop();
		virtual bool operator=();
		virtual int getIncome();

	private:
		super();
		int income;
};

#endif // Shop_h
