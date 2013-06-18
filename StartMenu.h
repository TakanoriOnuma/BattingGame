#ifndef ___Class_StartMenu
#define ___Class_StartMenu

#include "IScene.h"

class MyTeapot;
class StartMenu : public IScene{
	MyTeapot* teapot;

public:
	StartMenu();
	~StartMenu();

	IScene* update() override;
	void display() const override;
};

#endif