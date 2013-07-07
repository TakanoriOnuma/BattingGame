#ifndef ___Class_BattingRobot
#define ___Class_BattingRobot

#include "IBatter.h"
#include "MyRobot.h"

class MyBat;
class BattingRobot : public MyRobot, public IBatter{



	MyBat* bat;

	// �r�̊p�x�ύX�ɑ΂��鑬�x�Ɖ����x
	double accel_vec_r;
	double vec_r;
	double accel_vec_r2;
	double vec_r2;

	// �r�̍��W�ύX�ɑ΂��鑬�x�Ɖ����x
	Vector3d accel_vec_dis;
	Vector3d vec_dis;

	Point3d target;

protected:
	// --- State�N���X�̎����N���X --- //
	class Batting;


	void draw() const override;


public:
	using DrawableObject::draw;

	static const int SWING_FRAME = 30;


	BattingRobot(double x = 0.0, double y = 0.0, double z = 0.0);
	~BattingRobot();

	void update() override;

	void swing(const Point3d& target) override;

	int getFrame() const{
		return frame;
	}
	const Point3d& getTargetPoint() const{
		return target;
	}
};


#endif