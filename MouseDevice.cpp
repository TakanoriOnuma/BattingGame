#include "MouseDevice.h"
#include "MouseManager.h"
#include "Camera.h"

Game::MouseDevice::MouseDevice(BattingRobot& battingRobot, MyCircle& circle, Rectangle2D& batting_field, const Camera& camera)
	: UsingDevice(battingRobot, circle, batting_field), camera(camera)
{
	MouseManager::getInstance().addListener(this);
}

Game::MouseDevice::~MouseDevice()
{
	MouseManager::getInstance().removeListener(this);
}

// ===== UsingDevice�̃I�[�o�[���C�h ===== //
// �}�E�X�C�x���g�Ŏ��s���邽�߉������Ȃ�
void Game::MouseDevice::movePoint()
{
}
void Game::MouseDevice::swing()
{
}

// �C�x���g�̃Z�b�g�ƃ��Z�b�g
void Game::MouseDevice::setEventHandlar()
{
	MouseManager::getInstance().addListener(this);
	passive(0, 0);		// circle�̍��W���Z�b�g������
}
void Game::MouseDevice::resetEventHandlar()
{
	MouseManager::getInstance().removeListener(this);
}

// ===== MouseListener�̃I�[�o�[���C�h ===== //
void Game::MouseDevice::passive(int x, int y)
{
	// Z�o�b�t�@��p����3�������W�𓾂邽�߁A
	// �f�B�X�v���C�ɂ͕\�����Ȃ��Ă������`��`���Ă����ɓ�����悤�ɂ���B
	glLoadIdentity();				// ��x����������
	camera.setCamera();				// camera�̐ݒ���s��
	batting_field.drawField();		// �t�B�[���h��`������
	Point3d worldPoint = MouseManager::getInstance().getWorldPoint3d();

	const Point3d& field_pt = batting_field.getPoint();
	const Rectangle2D& field = batting_field;
	if(worldPoint.x > field_pt.x - field.getWidth() / 2 &&
		worldPoint.x < field_pt.x + field.getWidth() / 2 &&
		worldPoint.y > field_pt.y - field.getHeight() / 2 &&
		worldPoint.y < field_pt.y + field.getHeight() / 2 &&
		worldPoint.z > field_pt.z - 0.1 &&
		worldPoint.z < field_pt.z + 0.1){
			circle.move(worldPoint);
	}
}

void Game::MouseDevice::motion(int x, int y)
{
}

void Game::MouseDevice::mouse(int button, int state, int x, int y)
{
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
		battingRobot.swing(circle.getPoint());
	}
}

void Game::MouseDevice::wheel(int wheel_number, int direction, int x, int y)
{
}