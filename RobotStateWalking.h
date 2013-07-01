#ifndef ___Class_RobotStateWalking
#define ___Class_RobotStateWalking

#include "RobotState.h"

class MyRobot::Walking : public MyRobot::State{
	int max_frame;

	Walking();
	Walking(const Walking&);
public:
	void init(MyRobot& robot) const override;
	void update(MyRobot& robot) const override;
	void finish(MyRobot& robot) const override;

	static Walking* getInstance();
};

#endif