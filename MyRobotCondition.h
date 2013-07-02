#ifndef ___Enum_MyRobotCondition
#define ___Enum_MyRobotCondition

#include "MyRobot.h"

// --- エラーと出ているけど大丈夫 --- //
enum class MyRobot::Condition{
	STANDING,		// 立ち状態
	RUNNING,		// 走り状態
	SITTING,		// 座り状態
	JUMPING,		// ジャンプ状態
	WALKING,		// 歩き状態
};

#endif