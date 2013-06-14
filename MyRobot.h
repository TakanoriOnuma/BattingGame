#ifndef ___Class_MyRobot
#define ___Class_MyRobot

#include "DrawObject.h"

class MyBox;
class ArmLeg;

class MyRobot : public DrawObject{
	/* ���{�b�g�̏�� */
	enum class State;



	/* �ǂ�������O�ɏo���� */
/*
	enum WalkLeg{
		LEFT,			// ��
		RIGHT,			// �E

		SIZE,			// enum�̃T�C�Y
	};
*/
	static const int WALKING_FRAME = 50;		// ��������ɕK�v�ȃt���[����
	static const int RUNNING_FRAME = 40;		// ���铮��ɕK�v�ȃt���[����



	State   state;			// �����̏��
//	WalkLeg leg;			// �ǂ�������O�ɏo����

	struct MoveData;		// �t���[�����Ƃ̓���Ɏg���ړ��f�[�^�̍\����
	Vector3d vec;			// �ڍs��Ԃňړ������
	int direction;			// ����(1��-1�ŕ�����؂�ւ���)

/*
	double   vec_r1;		// �ڍs��Ԃŉ�]����r1
	double   arm_vec_r21;	// �ڍs��ԂŘr����]����r21
	double   arm_vec_r22;	// �ڍs��ԂŘr����]����r22
	double   leg_vec_r21;	// �ڍs��Ԃő�����]����r21
	double   leg_vec_r22;	// �ڍs��Ԃő�����]����r22
*/
	void setRectBox();

	void (MyRobot::*update_function)();		// update�p�֐�

protected:
	int frame;				// ���݂̃t���[����
	struct BodyParts;		// �̂̕��ʂ̍\����
	BodyParts* bodyParts;	// �̂̃p�[�c������

	void draw() const;

	void _walk_init();		// ������̓I�ȏ�����
	void _walk();			// ������̓I�ȉ^��
	void _run_init();		// �����̓I�ȏ�����
	void _run();			// �����̓I�ȉ^��

public:
	using DrawObject::draw;

	MyRobot(double x = 0.0, double y = 0.0, double z = 0.0);
	virtual ~MyRobot();

	virtual void update();

	void stand();
	void run();
	void sit();
	void jump();
	void walk();
};


#endif