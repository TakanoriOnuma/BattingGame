#ifndef ___Class_KeyboardDevice
#define ___Class_KeyboardDevice

#include "UsingDevice.h"

class Game::KeyboardDevice : public Game::UsingDevice{

public:
	KeyboardDevice(BattingRobot& battingRobot, MyCircle& circle, Rectangle2D& batting_field);

	void movePoint() override;
	void swing() override;
};

#endif