#include <iostream>
#include <math.h>

#include "PitchingRobotArm.h"
#include "RobotArm_Parts.h"
#include "MyBall.h"
#include "Rectangle2D.h"
#include "XorShift.h"
#include "MouseManager.h"

using namespace std;

PitchingRobotArm::PitchingRobotArm(double x, double y, double z)
	: RobotArm(x, y, z), frame(0), accel_vec_r(0.0), vec_r(0.0), ball(NULL), target_field(NULL)
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
	if(parts->joint.getAngle() > 0.0){
		if(ball != NULL){
			if(target_field == NULL){
				Point3d pt = this->getPoint();
				pt.y += this->getRectBox().height - parts->hand.getRectBox().height;

				double v = XorShift::instance().rand() % 50;
				v = v / 50.0 + 0.5;

				Point3d worldPt = MouseManager::getInstance().getWorldPoint3d();

				Vector3d vec(pt.x - worldPt.x, pt.y - worldPt.y, pt.z - worldPt.z);

				vec *= -v / sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);

				ball->move(pt);
				ball->setVector(vec.x, vec.y, vec.z);
				ball->emit();
				ball = NULL;
			}
			else{
				Point3d pt = this->getPoint();
				pt.y += this->getRectBox().height - parts->hand.getRectBox().height;
				ball->move(pt);

				int field_width  = static_cast<int>(target_field->getWidth());
				int field_height = static_cast<int>(target_field->getHeight());

				cout << "field(" << field_width << ", " << field_height << ")" << endl;

				double width  = XorShift::instance().rand() % (100 * field_width + 1);
				width = width / 100 - static_cast<double>(field_width) / 2;
				double height = XorShift::instance().rand() % (100 * field_height + 1);
				height = height / 100 - static_cast<double>(field_height) / 2;
				double v = XorShift::instance().rand() % 100;
				v = v / 300 + 1.0;

				cout << "target(" << width << ", " << height << ")" << endl;

				Vector3d vec;
				vec.x = (pt.x - target_field->getPoint().x) - width;
				vec.y = (pt.y - target_field->getPoint().y) - height;
				vec.z = (pt.z - target_field->getPoint().z);
				vec *= -v / sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
				double dis = pt.z - target_field->getPoint().z;
				vec.y += 1.0 / 2 * 0.005 * dis / -vec.z;

				cout << "vec(" << vec.x << ", " << vec.y << ", " << vec.z << "), ";
				cout << "|vec| = " << sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z) << endl;

				ball->setVector(vec.x, vec.y, vec.z);
				ball->emit();
				ball = NULL;
			}
		}
	}

	if(frame > THROWING_FRAME){
		frame = 0;
		update_function = NULL;
	}
}

void PitchingRobotArm::hand_ball(MyBall* ball)
{
	if(this->ball == NULL){
		this->ball = ball;
		this->ball->handed();		// ƒ{[ƒ‹‚ðŽ‚Â
		this->ball->move(Point3d(0.0, 0.0, 0.0));
	}
}