#ifndef ___Class_BattingRobot
#define ___Class_BattingRobot

#include "IBatter.h"
#include "MyRobot.h"

class MyBat;
class MyLine;
class BattingRobot : public MyRobot, public IBatter{

	static const int SWING_FRAME = 10;


	MyBat* bat;

	// �r�̊p�x�ύX�ɑ΂��鑬�x�Ɖ����x
	double accel_vec_r;
	double vec_r;
	double accel_vec_r2;
	double vec_r2;

	// �O�Ղ̈ړ��ɑ΂��鑬�x�Ɖ����x
	double vec_r_y;
	double vec_r_z;
	double accel_vec_r_y;
	double accel_vec_r_z;

	// �r�̍��W�ύX�ɑ΂��鑬�x�Ɖ����x
	Vector3d accel_vec_dis;
	Vector3d vec_dis;

	Point3d locus;		// �O��
	MyLine* line;		// �O�Ղ̗l�q������

protected:
	// --- State�N���X�̎����N���X --- //
	class Batting;


	void draw() const override;


public:
	using DrawableObject::draw;

	BattingRobot(double x = 0.0, double y = 0.0, double z = 0.0);
	~BattingRobot();

	void update() override;

	void swing() override;

};


#endif