#ifndef ___Class_IAnimation
#define ___Class_IAnimation

class IAnimation{

public:
	virtual ~IAnimation(){ }
	virtual void update() = 0;
};


#endif