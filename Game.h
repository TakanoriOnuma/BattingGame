#ifndef ___Class_Game
#define ___Class_Game

#include "IScene.h"

class MyLine;

class Camera;
class Game : public IScene{
	MyLine* line;

	struct DrawableObjects;
	DrawableObjects* objects;

	// --- デザインパターン Strategy --- //
	class HitProcesser;
	class RoughHitProcesser;
	class StandardHitProcesser;
	class StrictHitProcesser;

	HitProcesser* hitProcesser;		// 当たり判定を行うクラス

	Camera* camera;

	void check_char_key();
	void check_special_key();

public:
	Game();
	~Game();

	IScene* update() override;
	void display() const override;
};


#endif