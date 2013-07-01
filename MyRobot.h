#ifndef ___Class_MyRobot
#define ___Class_MyRobot

#include "DrawableObject.h"
#include "IAnimation.h"

class MyBox;
class ArmLeg;

class MyRobot : public DrawableObject, public IAnimation{
	/* ���{�b�g�̏�� */
	enum class Condition;
	Condition condition;			// �����̏��

	static const int WALKING_FRAME = 50;		// ��������ɕK�v�ȃt���[����
	static const int RUNNING_FRAME = 40;		// ���铮��ɕK�v�ȃt���[����

	Vector3d vec;			// �ڍs��Ԃňړ������
	int direction;			// ����(1��-1�ŕ�����؂�ւ���)

	void setRectBox();

	void (MyRobot::*update_function)();		// update�p�֐�

protected:


	int frame;				// ���݂̃t���[����
	struct BodyParts;		// �̂̕��ʂ̍\����
	BodyParts* bodyParts;	// �̂̃p�[�c������

	virtual void draw() const;

	void _walk_init();		// ������̓I�ȏ�����
	void _walk();			// ������̓I�ȉ^��
	void _run_init();		// �����̓I�ȏ�����
	void _run();			// �����̓I�ȉ^��

public:
	using DrawableObject::draw;

	MyRobot(double x = 0.0, double y = 0.0, double z = 0.0);
	virtual ~MyRobot();

	virtual void update() override;

	void stand();
	void run();
	void sit();
	void jump();
	void walk();
};


#endif