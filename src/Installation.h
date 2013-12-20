#ifndef Installation_h
#define Installation_h

class Installation {

 public:
	virtual Installation();
	virtual ~Installation();
	virtual Installation operator=();
    virtual void improve();
    virtual int getLevel();

 protected:
    int level;
};

#endif // Installation_h
