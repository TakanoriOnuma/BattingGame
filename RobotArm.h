#ifndef ___Class_RobotArm
#define ___Class_RobotArm

#include "DrawableObject.h"

class RobotArm : public DrawableObject{
	void setRectBox();

protected:
	struct Parts;		// PIMPLEパターンの使用
	Parts* parts;


	void draw() const;

public:
	using DrawableObject::draw;
	RobotArm(double x = 0.0, double y = 0.0, double z = 0.0);
	~RobotArm();

	void addArmAngle(double value);
	void setArmAngle(double angle);
	double getArmAngle() const;
};

#endif