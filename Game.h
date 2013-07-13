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
	const int MAX_BALL_NUM;		// 最大のボールの数
	std::string result_str;		// 結果

	class EmitionListener;			// MyBallがemitした時にメッセージを受け取るクラス
	EmitionListener* emitionListener;

	// --- デザインパターン Strategy --- //
	class HitProcesser;
	class NoDelayHitProcesser;
	class RoughHitProcesser;
	class StandardHitProcesser;
	class StrictHitProcesser;

	HitProcesser* hitProcesser;

	// --- デザインパターン Bridge --- //
	class UsingDevice;			// battingで使用するデバイス
	class KeyboardDevice;		// キーボードを使用
	class MouseDevice;			// マウスを使用

	UsingDevice* usingDevice;

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

	const Camera* getCamera() const{
		return camera;
	}

	void stop();		// イベントも受け取らないようにする
	void restart();		// 再開する
};


#endif