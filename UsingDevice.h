#ifndef ___Class_UsingDevice
#define ___Class_UsingDevice


#include "Game.h"

// どのクラスも以下のファイルはincludeするため
// 先にincludeする
#include "MyCircle.h"
#include "Rectangle2D.h"
#include "BattingRobot.h"

class Game::UsingDevice{

protected:
	// 必要なものだけ参照できるようにする
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

	// イベントを用いて処理する場合のセットとリセット
	virtual void setEventHandlar(){ }
	virtual void resetEventHandlar(){ }
};

#endif