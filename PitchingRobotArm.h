#ifndef ___Class_PitchingRobotArm
#define ___Class_PitchingRobotArm

#include "RobotArm.h"
#include "IPitcher.h"
#include "IAnimation.h"

class MyBall;
class Rectangle2D;
class PitchingRobotArm : public RobotArm, public IPitcher, public IAnimation{

	static const int THROWING_FRAME = 30;		// 投げる動作に必要なフレーム数

	MyBall* ball;

	int frame;				// フレーム数

	double accel_vec_r;		// 角加速度
	double vec_r;			// 加速度

	const Rectangle2D* target_field;		// 投げる範囲

	void (PitchingRobotArm::*update_function)();	// update用関数

protected:
	void draw() const override;

	void _ball_throw_init();
	void _ball_throw();

public:
	using DrawableObject::draw;

	PitchingRobotArm(double x = 0.0, double y = 0.0, double z = 0.0);

	void update() override;

	void ball_throw();
	void hand_ball(MyBall* ball);		// ボールを持つ

	void setTargetField(const Rectangle2D* target_field){
		this->target_field = target_field;
	}
	bool isSetTargetField() const{
		return target_field != NULL;
	}
};


#endif