#ifndef ___Class_Game
#define ___Class_Game

#include "IScene.h"
#include <string>

class Camera;
class Game : public IScene{
	struct DrawableObjects;
	DrawableObjects* objects;

	int score;					// �X�R�A
	int ball_num;				// �c��̃{�[���̐�
	std::string result_str;		// ����

	class GameMouseListener;		// MouseListener
	GameMouseListener* mouseListener;

	class EmitionListener;			// MyBall��emit�������Ƀ��b�Z�[�W���󂯎��N���X
	EmitionListener* emitionListener;

	// --- �f�U�C���p�^�[�� Strategy --- //
	class HitProcesser;
	class NoDelayHitProcesser;
	class RoughHitProcesser;
	class StandardHitProcesser;
	class StrictHitProcesser;

	HitProcesser* hitProcesser;

	Camera* camera;

	void check_char_key();
	void check_special_key();

	bool check_flag;		// �`�F�b�N���邩
	void check_ball();

public:
	Game();
	~Game();

	IScene* update() override;
	void display() const override;
};


#endif