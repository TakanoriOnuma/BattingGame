#ifndef ___Class_RobotArm
#define ___Class_RobotArm

#include "DrawObject.h"

class RobotArm : public DrawObject{
	void setRectBox();

protected:
	struct Parts;		// PIMPLE�p�^�[���̎g�p
	Parts* parts;


	void draw() const;

public:
	using DrawObject::draw;
	RobotArm(double x = 0.0, double y = 0.0, double z = 0.0);
	~RobotArm();

	void addArmAngle(double value);
	void setArmAngle(double angle);
};

#endif