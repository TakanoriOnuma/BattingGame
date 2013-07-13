#ifndef ___Class_MouseDevice
#define ___Class_MouseDevice

#include "UsingDevice.h"
#include "MouseListener.h"

class Game::MouseDevice : public UsingDevice, public MouseListener{
	const Camera& camera;

public:
	MouseDevice(BattingRobot& battingRobot, MyCircle& circle, Rectangle2D& batting_field, const Camera& camera);
	~MouseDevice();

	// UsingDevice�̃I�[�o�[���C�h
	void movePoint() override;
	void swing() override;

	// �C�x���g�̃Z�b�g�ƃ��Z�b�g
	void setEventHandlar() override;
	void resetEventHandlar() override;

	// MouseListener�̃I�[�o�[���C�h
	void passive(int x, int y) override;
	void motion(int x, int y) override;
	void mouse(int button, int state, int x, int y) override;
	void wheel(int wheel_number, int direction, int x, int y) override;
};

#endif