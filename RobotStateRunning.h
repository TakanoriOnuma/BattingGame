#ifndef ___Class_RobotStateRunnning
#define ___Class_RobotStateRunnning

#include "RobotState.h"

class MyRobot::Running : public MyRobot::State{
	int max_frame;

	Running();
	Running(const Running&);
public:
	void init(MyRobot& robot) const override;
	void update(MyRobot& robot) const override;
	void finish(MyRobot& robot) const override;

	static Running* getInstance();
};

#endif