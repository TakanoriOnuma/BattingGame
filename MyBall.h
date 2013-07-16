#ifndef ___Class_MyBall
#define ___Class_MyBall

#include "MySphere.h"
#include "IAnimation.h"
#include "MyVector.h"
#include "EmitionMesseage.h"

class MyBall : public MySphere, public IAnimation{
public:
	enum class State{
		ISOLATED,		// �Ɨ����Ă���
		HANDED,			// �N���Ɏ�����Ă���
	};

	// --- ���� --- //
	enum class EVariety{
		SLOWBALL,		// �X���[�{�[��
		STRAIGHT,		// �X�g���[�g
		CURVE,			// �J�[�u
		SHOOT,			// �V���[�g
		SLIDER,			// �X���C�_�[
		FOLK,			// �t�H�[�N
		CHENGEUP,		// �`�F���W�A�b�v
		GYRO,			// �W���C���{�[��

		SIZE,			// �T�C�Y
	};

	// --- �f�U�C���p�^�[�� State --- //
	class Variety;
	class SlowBall;		// �X���[�{�[���Ƃ�����薳�ω��̃{�[��
	class Straight;		// ���������オ��{�[��
	class Curve;
	class Slider;
	class Folk;
	class ChengeUp;
	class Gyro;

private:
	State    state;		// �������
	Variety* variety;	// ����
	Vector3d vec;		// �ړ��x�N�g��
	double   gravity;	// �d��

	unsigned int texNumber;		// �e�N�X�`���̔ԍ�

	EmitionMessage* message;		// emit�����s�������ɒʒm����I�u�U�[�o�[

	void init();

protected:
	void draw() const override;

public:
	using DrawableObject::draw;

	MyBall(double radius = 1.0, int sides = 16);
	MyBall(double x, double y, double z, double radius = 1.0, int sides = 16);
	~MyBall();

	void update() override;

	const State& getState() const{
		return state;
	}

	// ��������
	void emit(Variety* variety);

	// �N���Ɏ������
	void handed(){
		state = State::HANDED;
	}

	void setEmitionMessage(EmitionMessage* message){
		this->message = message;
	}

	void setVector(double x, double y, double z){
		vec.x = x;
		vec.y = y;
		vec.z = z;
	}
	const Vector3d& getVector() const{
		return vec;
	}
	double getGravity() const{
		return gravity;
	}
};

#endif