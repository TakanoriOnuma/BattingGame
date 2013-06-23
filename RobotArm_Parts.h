#ifndef ___Class_RobotArm_Parts
#define ___Class_RobotArm_Parts

#include "RobotArm.h"
#include "MyCylinder.h"
#include "MyBox.h"

struct RobotArm::Parts
{
	MyCylinder foundation;		// �y��
	MyBox      first_arm;		// 1�Ԗڂ̃A�[��
	MyCylinder joint;			// �֐�
	MyBox      second_arm;		// 2�Ԗڂ̃A�[��
	MyBox      hand;			// �n���h

	// --- �R���X�g���N�^ --- //
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