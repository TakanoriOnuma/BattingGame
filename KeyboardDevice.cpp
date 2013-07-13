#include "KeyboardDevice.h"
#include "KeyboardManager.h"

Game::KeyboardDevice::KeyboardDevice(BattingRobot& battingRobot, MyCircle& circle, Rectangle2D& batting_field)
	: UsingDevice(battingRobot, circle, batting_field)
{
}

void Game::KeyboardDevice::movePoint()
{
	KeyboardManager& keyManager = KeyboardManager::getInstance();

	if(keyManager.isPushSpecialKey(SpecialKey::LEFT)){
		circle.move(Vector3d(-0.1, 0.0, 0.0));
		if(circle.getPoint().x < batting_field.getPoint().x - batting_field.getWidth() / 2){
			Point3d pt(circle.getPoint());
			pt.x = batting_field.getPoint().x - batting_field.getWidth() / 2;
			circle.move(pt);
		}
	}
	else if(keyManager.isPushSpecialKey(SpecialKey::RIGHT)){
		circle.move(Vector3d(0.1, 0.0, 0.0));
		if(circle.getPoint().x > batting_field.getPoint().x + batting_field.getWidth() / 2){
			Point3d pt(circle.getPoint());
			pt.x = batting_field.getPoint().x + batting_field.getWidth() / 2;
			circle.move(pt);
		}
	}

	if(keyManager.isPushSpecialKey(SpecialKey::DOWN)){
		circle.move(Vector3d(0.0, -0.1, 0.0));
		if(circle.getPoint().y < batting_field.getPoint().y - batting_field.getHeight() / 2){
			Point3d pt(circle.getPoint());
			pt.y = batting_field.getPoint().y - batting_field.getHeight() / 2;
			circle.move(pt);
		}
	}
	else if(keyManager.isPushSpecialKey(SpecialKey::UP)){
		circle.move(Vector3d(0.0, 0.1, 0.0));
		if(circle.getPoint().y > batting_field.getPoint().y + batting_field.getHeight() / 2){
			Point3d pt(circle.getPoint());
			pt.y = batting_field.getPoint().y + batting_field.getHeight() / 2;
			circle.move(pt);
		}
	}
}

void Game::KeyboardDevice::swing()
{
	if(KeyboardManager::getInstance().isPushCharKey(' ')){
		battingRobot.swing(circle.getPoint());
	}
}