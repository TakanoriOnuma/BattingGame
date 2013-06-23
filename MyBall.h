#ifndef ___Class_MyBall
#define ___Class_MyBall

#include "MySphere.h"
#include "IAnimation.h"
#include "MyVector.h"

class MyBall : public MySphere, public IAnimation{
public:
	enum class State{
		ISOLATED,		// �Ɨ����Ă���
		HANDED,			// �N���Ɏ�����Ă���
	};

private:
	State state;		// �������
	Vector3d vec;		// �ړ��x�N�g��

public:
	MyBall();

	void update() override;

	const State& getState() const{
		return state;
	}

	// ��������
	void emit(){
		state = State::ISOLATED;
	}

	// �N���Ɏ������
	void handed(){
		state = State::HANDED;
	}

	void setVector(double x, double y, double z){
		vec.x = x;
		vec.y = y;
		vec.z = z;
	}
};

#endif