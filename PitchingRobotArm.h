#ifndef ___Class_PitchingRobotArm
#define ___Class_PitchingRobotArm

#include "IPitcher.h"
#include "RobotArm.h"

class PitchingRobotArm : public RobotArm, public IPitcher{

	static const int THROWING_FRAME = 30;		// 投げる動作に必要なフレーム数

	int frame;				// フレーム数

	double accel_vec_r;		// 角加速度
	double vec_r;			// 加速度

	void (PitchingRobotArm::*update_function)();	// update用関数

protected:
	void _ball_throw_init();
	void _ball_throw();

public:
	PitchingRobotArm(double x = 0.0, double y = 0.0, double z = 0.0);

	void update();

	void ball_throw();

};


#endif