#include "NormalThrowingBall.h"
#include "XorShift.h"
#include "BallSlowBall.h"
#include "BallStraight.h"

#include <iostream>

using namespace std;

// 内部に変数を持たせてシングルトンを実装する
PitchingRobotArm::NormalThrowingBall* PitchingRobotArm::NormalThrowingBall::getInstance()
{
	static NormalThrowingBall normalThrowingBall;
	return &normalThrowingBall;
}

void PitchingRobotArm::NormalThrowingBall::throwBall
	(const Point3d& throw_point, const Rectangle2D* target_field, MyBall& ball) const
{
	if(target_field == NULL){
		double vec = XorShift::instance().rand() % 50;
		vec = vec / 50.0 + 0.5;

		ball.setVector(0.0, 0.0, vec);
//		ball.emit(MyBall::Variety::STRAIGHT);	// ストレートを投げる
	}
	else{
		int field_width  = static_cast<int>(target_field->getWidth());
		int field_height = static_cast<int>(target_field->getHeight());

		cout << "field(" << field_width << ", " << field_height << ")" << endl;

		double width  = XorShift::instance().rand() % (100 * field_width + 1);
		width = width / 100 - static_cast<double>(field_width) / 2;
		double height = XorShift::instance().rand() % (100 * field_height + 1);
		height = height / 100 - static_cast<double>(field_height) / 2;
		double v = XorShift::instance().rand() % 100;
//		v = v / 100 + 0.5;
		v = 1.0;

		cout << "target(" << width << ", " << height << ")" << endl;

		Vector3d vec;
		vec.x = (throw_point.x - target_field->getPoint().x) - width;
		vec.y = (throw_point.y - target_field->getPoint().y) - height;
		vec.z = (throw_point.z - target_field->getPoint().z);
		vec *= -v / vec.getMagnitude();
		double dis = throw_point.z - target_field->getPoint().z;

		if(vec.getMagnitude() <= 1.0){
			vec.y += 1.0 / 2 * ball.getGravity() * dis / -vec.z;

			cout << "vec(" << vec.x << ", " << vec.y << ", " << vec.z << "), ";
			cout << "|vec| = " << vec.getMagnitude() << endl;

			ball.setVector(vec.x, vec.y, vec.z);

			ball.emit(new MyBall::SlowBall());
		}
		else{
			vec.y += 1.0 / 2 * (0.7 * ball.getGravity()) * dis / -vec.z;

			cout << "vec(" << vec.x << ", " << vec.y << ", " << vec.z << "), ";
			cout << "|vec| = " << vec.getMagnitude() << endl;

			ball.setVector(vec.x, vec.y, vec.z);
			ball.emit(new MyBall::Straight(0.3 * ball.getGravity()));
		}
	}

}