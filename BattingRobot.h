#ifndef ___Class_BattingRobot
#define ___Class_BattingRobot

#include "IBatter.h"
#include "MyRobot.h"

class MyBat;
class BattingRobot : public MyRobot, public IBatter{

	static const int SWING_FRAME = 50;


	MyBat* bat;

	double accel_vec_r;
	double vec_r;


	void (BattingRobot::*update_function)();

protected:
	void draw() const override;

	void _swing_init();
	void _swing();


public:
	BattingRobot(double x = 0.0, double y = 0.0, double z = 0.0);
	~BattingRobot();

	void update() override;

	void swing() override;

};


#endif