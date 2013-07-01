#ifndef ___Class_RobotState
#define ___Class_RobotState

#include "MyRobot.h"

class MyRobot::State{
public:
	virtual ~State(){ }

	virtual void init(MyRobot& robot) const = 0;
	virtual void update(MyRobot& robot) const = 0;
	virtual void finish(MyRobot& robot) const = 0;
};

#endif