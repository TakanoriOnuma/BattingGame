#ifndef ___Class_Game
#define ___Class_Game

#include "IScene.h"

class Game : public IScene{
	struct DrawObjects;
	DrawObjects* objects;

	double angle;

	void check_char_key();
	void check_special_key();

public:
	Game();
	~Game();

	IScene* update() override;
	void display() const override;
};


#endif