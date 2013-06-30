#ifndef ___Class_RobotArm_Parts
#define ___Class_RobotArm_Parts

#include "RobotArm.h"
#include "MyCylinder.h"
#include "MyBox.h"

struct RobotArm::Parts
{
	MyCylinder foundation;		// 土台
	MyBox      first_arm;		// 1番目のアーム
	MyCylinder joint;			// 関節
	MyBox      second_arm;		// 2番目のアーム
	MyBox      hand;			// ハンド

	// --- コンストラクタ --- //
	Parts()
		: foundation(0.0, 0.0, 0.0, 0.5, 0.2, 16),
		first_arm   (0.0, 1.1, 0.0, 0.3, 0.3, 1.0),
		joint       (0.0, 0.1, 0.0, 0.2, 0.4, 16),
		second_arm  (0.0, 1.0, 0.0, 0.3, 0.3, 1.0),
		hand        (0.0, 0.5, 0.0, 0.5, 0.5, 0.5)
	{
	}
};


#endif