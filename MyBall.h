#ifndef ___Class_MyBall
#define ___Class_MyBall

#include "MySphere.h"
#include "IAnimation.h"
#include "MyVector.h"

class MyBall : public MySphere, public IAnimation{
public:
	enum class State{
		ISOLATED,		// 独立している
		HANDED,			// 誰かに持たれている
	};

private:
	State state;		// 内部状態
	Vector3d vec;		// 移動ベクトル

	void draw() const override;

public:
	using DrawableObject::draw;

	MyBall(double radius = 1.0, int sides = 16);
	MyBall(double x, double y, double z, double radius = 1.0, int sides = 16);

	void update() override;

	const State& getState() const{
		return state;
	}

	// 解き放つ
	void emit(){
		state = State::ISOLATED;
	}

	// 誰かに持たれる
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