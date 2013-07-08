#ifndef ___Class_GameDecorator
#define ___Class_GameDecorator

#include "IScene.h"

class Game;
// Game Sceneに責任を追加させるクラス
// デザインパターン Decorator
class GameDecorator : public IScene{
	Game* game;				// ゲームポインタを持つ
	bool  pause_flag;		// ポーズをしているか

public:
	GameDecorator();
	~GameDecorator();

	IScene* update() override;
	void display() const override;
};


#endif