#ifndef ___Class_RobotStateBatting
#define ___Class_RobotStateBatting

#include "RobotState.h"
#include "BattingRobot.h"

class BattingRobot::Batting : public MyRobot::State{
	int max_frame;

	Batting();
	Batting(const Batting&);
public:
	void init(MyRobot& robot) const override;
	void update(MyRobot& robot) const override;
	void finish(MyRobot& robot) const override;

	static Batting* getInstance();
};

#endif