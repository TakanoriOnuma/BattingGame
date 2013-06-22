#ifndef ___Class_StartMenu
#define ___Class_StartMenu

#include "IScene.h"

class Camera;
class StartMenu : public IScene{
	struct DrawObjects;
	DrawObjects* objects;
	Camera* camera;

	double angle_xz;
	double angle_yz;

	void check_char_key();
	void check_special_key();

public:
	StartMenu();
	~StartMenu();

	IScene* update() override;
	void display() const override;
};

#endif