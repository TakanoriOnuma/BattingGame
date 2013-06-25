#include <iostream>
#include <math.h>

#include "PitchingRobotArm.h"
#include "RobotArm_Parts.h"
#include "MyBall.h"
#include "Rectangle2D.h"
#include "XorShift.h"

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

				double vec = XorShift::instance().rand() % 50;
				vec = vec / 50.0 + 0.5;

				ball->move(pt);
				ball->setVector(0.0, 0.0, vec);		// �X�g���[�g�𓊂���
				ball->emit();
				ball = NULL;
			}
			else{
				Point3d pt = this->getPoint();
				pt.y += this->getRectBox().height - parts->hand.getRectBox().height;
				ball->move(pt);

				double distance = this->getPoint().z - target_field->getPoint().z;		// z���̋��������߂�
				int field_width  = static_cast<int>(target_field->getWidth());
				int field_height = static_cast<int>(target_field->getHeight());

				double width  = XorShift::instance().rand() % (100 * field_width + 1);
				width = width / 100 - field_width / 2;
				double height = XorShift::instance().rand() % (100 * field_height + 1);
				height = height / 100 - field_height / 2;
				height -= pt.y - target_field->getPoint().y;		// ��������W�ƃ^�[�Q�b�g���W�̍����l������
				double v = XorShift::instance().rand() % 100;
				v = v / 100 + 0.5;

				cout << "target(" << width << ", " << height << ")" << endl;


				double theta = atan2(distance, width);
				double phi = atan2(height, sqrt(width * width + distance * distance));

				double tiltVector = v * cos(phi);

				Vector3d vec;

				vec.x = tiltVector * cos(-theta);
				vec.y = v * sin(phi);
				vec.z = tiltVector * sin(-theta);

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
		this->ball->handed();		// �{�[��������
		this->ball->move(Point3d(0.0, 0.0, 0.0));
	}
}