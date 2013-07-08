#ifndef ___Class_GameDecorator
#define ___Class_GameDecorator

#include "IScene.h"

class Game;
// Game Scene�ɐӔC��ǉ�������N���X
// �f�U�C���p�^�[�� Decorator
class GameDecorator : public IScene{
	Game* game;				// �Q�[���|�C���^������
	bool  pause_flag;		// �|�[�Y�����Ă��邩

public:
	GameDecorator();
	~GameDecorator();

	IScene* update() override;
	void display() const override;
};


#endif