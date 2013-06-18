#ifndef ___Class_Game
#define ___Class_Game

#include "IScene.h"

class Game : public IScene{
	struct DrawObjects;
	DrawObjects* objects;

public:
	Game();
	~Game();

	IScene* update() override;
	void display() const override;
};


#endif