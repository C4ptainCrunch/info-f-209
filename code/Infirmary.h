#ifndef Infirmary_h
#define Infirmary_h

#include "Installation.h"


/*
 */
class Infirmary : public Installation, virtual public Installation {

 public:

    virtual void heal();
};

#endif // Infirmary_h
