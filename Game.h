#ifndef ___Class_Game
#define ___Class_Game

#include "IScene.h"
#include <string>

class Camera;
class Game : public IScene{
	struct DrawableObjects;
	DrawableObjects* objects;

	int score;					// スコア
	int ball_num;				// 残りのボールの数
	std::string result_str;		// 結果

	class GameMouseListener;		// MouseListener
	GameMouseListener* mouseListener;

	class EmitionListener;			// MyBallがemitした時にメッセージを受け取るクラス
	EmitionListener* emitionListener;

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