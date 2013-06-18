#ifndef ___Class_Game
#define ___Class_Game

#include "IScene.h"

class MyBox;
class Game : public IScene{
	MyBox* box;

public:
	Game();
	~Game();

	IScene* update() override;
	void display() const override;
};


#endif