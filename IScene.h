#ifndef ___Class_IScene
#define ___Class_IScene

class IScene{

public:
	virtual ~IScene(){ }

	virtual IScene* update() = 0;
	virtual void display() const = 0;
};


#endif