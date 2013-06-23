#include <math.h>

#include "PitchingRobotArm.h"
#include "MyBall.h"

PitchingRobotArm::PitchingRobotArm(double x, double y, double z)
	: RobotArm(x, y, z), frame(0), accel_vec_r(0.0), vec_r(0.0), ball(NULL)
{
	update_function = NULL;
}

void PitchingRobotArm::draw() const
{
	RobotArm::draw();
	if(ball != NULL && ball->getState() == MyBall::State::HANDED){
		ball->draw(true, true);
	}
}

void PitchingRobotArm::update()
{
	if(update_function != NULL){
		(this->*update_function)();
	}
}

void PitchingRobotArm::ball_throw()
{
	if(frame == 0){
		update_function = &PitchingRobotArm::_ball_throw;
		_ball_throw_init();
	}
}

void PitchingRobotArm::_ball_throw_init()
{
	double angle = 90.0;
		setArmAngle(0.0);

	accel_vec_r = (8.0 + 4 * sqrt(5.0)) * angle / (THROWING_FRAME * THROWING_FRAME);
	vec_r = 2.0 * angle / THROWING_FRAME - accel_vec_r * THROWING_FRAME / 2.0;
}

void PitchingRobotArm::_ball_throw()
{
	addArmAngle(vec_r);
	vec_r += accel_vec_r;

	frame++;
	if(frame > THROWING_FRAME){
		frame = 0;
		update_function = NULL;
	}
}

void PitchingRobotArm::hand_ball(MyBall* ball)
{
	if(this->ball == NULL){
		this->ball = ball;
		this->ball->handed();		// ƒ{[ƒ‹‚ğ‚Â
	}
}