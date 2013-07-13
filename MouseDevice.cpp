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

// ===== UsingDeviceのオーバーライド ===== //
// マウスイベントで実行するため何もしない
void Game::MouseDevice::movePoint()
{
}
void Game::MouseDevice::swing()
{
}

// イベントのセットとリセット
void Game::MouseDevice::setEventHandlar()
{
	MouseManager::getInstance().addListener(this);
	passive(0, 0);		// circleの座標をセットさせる
}
void Game::MouseDevice::resetEventHandlar()
{
	MouseManager::getInstance().removeListener(this);
}

// ===== MouseListenerのオーバーライド ===== //
void Game::MouseDevice::passive(int x, int y)
{
	// Zバッファを用いて3次元座標を得るため、
	// ディスプレイには表示しなくても長方形を描いてそこに当たるようにする。
	glLoadIdentity();				// 一度初期化する
	camera.setCamera();				// cameraの設定を行う
	batting_field.drawField();		// フィールドを描かせる
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