#include "Game.h"
#include "MyBox.h"

#include <iostream>

using namespace std;

Game::Game()
{
	box = new MyBox();
}

Game::~Game()
{
	delete box;
}

IScene* Game::update()
{
	return this;
}

void Game::display() const
{
	cout << "call Game display" << endl;

	/* ��ʃN���A */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/* ���f���E�r���[�ϊ��s��̏����� */
	glLoadIdentity();

	/* ���_�̈ړ�(���̂̕������Ɉڂ�) */
	glTranslated(0.0, 0.0, -5.0);

	box->draw(true, true);

	glutSolidCube(1.0);
}