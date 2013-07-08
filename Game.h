#ifndef ___Class_Game
#define ___Class_Game

#include "IScene.h"

class Camera;
class Game : public IScene{
	struct DrawableObjects;
	DrawableObjects* objects;

	int score;		// スコア

	class GameMouseListener;		// MouseListener
	GameMouseListener* mouseListener;

	// --- デザインパターン Strategy --- //
	class HitProcesser;
	class NoDelayHitProcesser;
	class RoughHitProcesser;
	class StandardHitProcesser;
	class StrictHitProcesser;

	HitProcesser* hitProcesser;

	Camera* camera;

	void check_char_key();
	void check_special_key();

	bool check_flag;		// チェックするか
	void check_ball();

public:
	Game();
	~Game();

	IScene* update() override;
	void display() const override;
};


#endif