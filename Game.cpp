#include "Game.h"
#include "Ground.h"
#include "BattingRobot.h"
#include "PitchingRobotArm.h"
#include "MaterialData.h"
#include "KeyboardManager.h"

#include <iostream>

using namespace std;

struct Game::DrawObjects{
	Ground ground;
	BattingRobot battingRobot;
	PitchingRobotArm pitchingRobotArm;

	DrawObjects()
		: ground(0.0, -1.8, 0.0),
		battingRobot(0.0, 0.9, 1.0),
		pitchingRobotArm(0.0, -1.5, -3.0)
	{
		battingRobot.setRotateVector(0.0, 1.0, 0.0);
		battingRobot.setMaterialData(MaterialData::createMaterialData(Jewel::TURQUOISE));
		pitchingRobotArm.setMaterialData(MaterialData::createMaterialData(Ore::BRONZE));
	}

	void draw() const{
		ground.draw(true, true);
		battingRobot.draw(true, true);
		pitchingRobotArm.draw(true, true);
	}

	// 必要のあるものだけupdateする
	void update(){
		battingRobot.update();
		pitchingRobotArm.update();
	}
};

Game::Game()
	: angle(0.0)
{
	objects = new DrawObjects();
}

Game::~Game()
{
	delete objects;
}

void Game::check_char_key()
{
	KeyboardManager& keyboardManager = KeyboardManager::getKeyboardManager();
	if(keyboardManager.isPushCharKey('t')){
		objects->battingRobot.swing();
	}
	if(keyboardManager.isPushCharKey('o')){
		objects->pitchingRobotArm.ball_throw();
	}

	if(keyboardManager.isPushCharKey('a')){
		angle += 1.0;
	}
	else if(keyboardManager.isPushCharKey('d')){
		angle -= 1.0;
	}
}

void Game::check_special_key()
{
	KeyboardManager& keyboardManager = KeyboardManager::getKeyboardManager();

	if(keyboardManager.isPushSpecialKey(SpecialKey::LEFT)){
		objects->battingRobot.addAngle(-5.0);
	}
	else if(keyboardManager.isPushSpecialKey(SpecialKey::RIGHT)){
		objects->battingRobot.addAngle(5.0);
	}

	if(keyboardManager.isPushSpecialKey(SpecialKey::UP)){
		if(keyboardManager.isPushCharKey('r')){
			objects->battingRobot.run();
		}
		else{
			objects->battingRobot.walk();
		}
	}
}

IScene* Game::update()
{
	objects->update();

	check_char_key();
	check_special_key();

	return this;
}


void Game::display() const
{
	static GLfloat lightpos0[] = { 3.0, 4.0, 5.0, 1.0 };
	static GLfloat lightpos1[] = {-3.0, 4.0, 5.0, 1.0 };
	/* 画面クリア */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/* モデル・ビュー変換行列の初期化 */
	glLoadIdentity();

	/* 視点の移動(物体の方を奥に移す) */
	glTranslated(0.0, 0.0, -13.0);
	glRotated(angle, 0.0, 1.0, 0.0);

	/* 光源の位置を指定 */
	glLightfv(GL_LIGHT0, GL_POSITION, lightpos0);
	glLightfv(GL_LIGHT1, GL_POSITION, lightpos1);

	objects->draw();

	glutSwapBuffers();
}