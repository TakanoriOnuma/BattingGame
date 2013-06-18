#include "Game.h"
#include "Ground.h"
#include "BattingRobot.h"
#include "PitchingRobotArm.h"
#include "MaterialData.h"

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
		battingRobot.setMaterialData(MaterialData::createMaterialData(Jewel::TURQUOISE));
		pitchingRobotArm.setMaterialData(MaterialData::createMaterialData(Ore::BRONZE));
	}

	void draw() const{
		ground.draw(true, true);
		battingRobot.draw(true, true);
		pitchingRobotArm.draw(true, true);
	}

};

Game::Game()
{
	objects = new DrawObjects();
}

Game::~Game()
{
	delete objects;
}

IScene* Game::update()
{
	return this;
}


void Game::display() const
{
	cout << "call Game display" << endl;
	static GLfloat lightpos0[] = { 3.0, 4.0, 5.0, 1.0 };
	static GLfloat lightpos1[] = {-3.0, 4.0, 5.0, 1.0 };
	/* ��ʃN���A */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/* ���f���E�r���[�ϊ��s��̏����� */
	glLoadIdentity();

	/* ���_�̈ړ�(���̂̕������Ɉڂ�) */
	glTranslated(0.0, 0.0, -13.0);
	glRotated(30.0, 0.0, 1.0, 0.0);

	/* �����̈ʒu���w�� */
	glLightfv(GL_LIGHT0, GL_POSITION, lightpos0);
	glLightfv(GL_LIGHT1, GL_POSITION, lightpos1);

	objects->draw();


	glutSwapBuffers();
}