#ifndef ___Class_IPitcher
#define ___Class_IPitcher

class IPitcher{

public:
	virtual ~IPitcher(){ }
	virtual void ball_throw() = 0;
};

#endif