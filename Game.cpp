#include "Game.h"
#include "Ground.h"
#include "BattingRobot.h"
#include "PitchingRobotArm.h"
#include "MaterialData.h"
#include "KeyboardManager.h"
#include "Camera.h"
#include "MyBall.h"
#include "Rectangle2D.h"

#include <iostream>

using namespace std;

struct Game::DrawableObjects{
	MyBall ball;
	Ground ground;
	BattingRobot battingRobot;
	PitchingRobotArm pitchingRobotArm;

	Rectangle2D batting_field;

	DrawableObjects()
		: ball(0.3),
		ground(0.0, -1.8, -5.0, 10, 20),
		battingRobot(-2.0, 0.9, 3.0),
		pitchingRobotArm(0.0, -1.5, -13.0),
		batting_field(0.0, 0.0, 3.0, 2.0, 2.0, ColorData(1.0, 0.0, 0.0))
	{
		ball.setMaterialData(MaterialData::createMaterialData(Jewel::OBSIDIAN));
		battingRobot.setRotateVector(0.0, 1.0, 0.0);
		battingRobot.setAngle(90.0);
		battingRobot.setMaterialData(MaterialData::createMaterialData(Jewel::TURQUOISE));
		pitchingRobotArm.setMaterialData(MaterialData::createMaterialData(Ore::BRONZE));
		pitchingRobotArm.hand_ball(&ball);
		pitchingRobotArm.setTargetField(&batting_field);
	}

	void draw() const{
		if(ball.getState() != MyBall::State::HANDED){
			ball.draw(true, true);
		}
		ground.draw(true, true);
		battingRobot.draw(true, true);
		pitchingRobotArm.draw(true, true);

		batting_field.draw(true, true);
	}

	// 必要のあるものだけupdateする
	void update(){
		ball.update();
		battingRobot.update();
		pitchingRobotArm.update();
	}
};

Game::Game()
{
	objects = new DrawableObjects();
	camera  = new Camera();
}

Game::~Game()
{
	delete objects;
	delete camera;
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
	if(keyboardManager.isPushCharKey('h')){
		objects->pitchingRobotArm.hand_ball(&objects->ball);	// ボールを持たせる
	}
	if(keyboardManager.isPushCharKey('k')){
		objects->pitchingRobotArm.setTargetField(&objects->batting_field);
	}
	else if(keyboardManager.isPushCharKey('l')){
		objects->pitchingRobotArm.setTargetField(NULL);
	}

	// --- カメラの調整 --- //
	if(keyboardManager.isPushCharKey('a')){
		camera->addAngle_xz(5.0);
	}
	else if(keyboardManager.isPushCharKey('d')){
		camera->addAngle_xz(-5.0);
	}
	if(keyboardManager.isPushCharKey('w')){
		camera->addDistance(-1.0);
	}
	else if(keyboardManager.isPushCharKey('s')){
		camera->addDistance(1.0);
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

	/* カメラのセット */
	camera->setCamera();

	/* 光源の位置を指定 */
	glLightfv(GL_LIGHT0, GL_POSITION, lightpos0);
	glLightfv(GL_LIGHT1, GL_POSITION, lightpos1);

	objects->draw();

	glutSwapBuffers();
}