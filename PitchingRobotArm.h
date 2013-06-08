#ifndef ___Class_PitchingRobotArm
#define ___Class_PitchingRobotArm

#include "IPitcher.h"
#include "RobotArm.h"

class PitchingRobotArm : public RobotArm, public IPitcher{

	static const int THROWING_FRAME = 30;		// �����铮��ɕK�v�ȃt���[����

	int frame;				// �t���[����

	double accel_vec_r;		// �p�����x
	double vec_r;			// �����x

	void (PitchingRobotArm::*update_function)();	// update�p�֐�

protected:
	void _ball_throw_init();
	void _ball_throw();

public:
	PitchingRobotArm(double x = 0.0, double y = 0.0, double z = 0.0);

	void update();

	void ball_throw();

};


#endif