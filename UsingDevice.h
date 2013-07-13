#ifndef ___Class_UsingDevice
#define ___Class_UsingDevice


#include "Game.h"

// �ǂ̃N���X���ȉ��̃t�@�C����include���邽��
// ���include����
#include "MyCircle.h"
#include "Rectangle2D.h"
#include "BattingRobot.h"

class Game::UsingDevice{

protected:
	// �K�v�Ȃ��̂����Q�Ƃł���悤�ɂ���
	BattingRobot& battingRobot;
	MyCircle&     circle;
	Rectangle2D&  batting_field;

public:
	UsingDevice(BattingRobot& battingRobot, MyCircle& circle, Rectangle2D& batting_field)
		: battingRobot(battingRobot), circle(circle), batting_field(batting_field)
	{
	}

	virtual ~UsingDevice(){ }

	virtual void movePoint() = 0;
	virtual void swing() = 0;

	// �C�x���g��p���ď�������ꍇ�̃Z�b�g�ƃ��Z�b�g
	virtual void setEventHandlar(){ }
	virtual void resetEventHandlar(){ }
};

#endif