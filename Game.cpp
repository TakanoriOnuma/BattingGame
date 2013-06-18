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

	/* 画面クリア */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/* モデル・ビュー変換行列の初期化 */
	glLoadIdentity();

	/* 視点の移動(物体の方を奥に移す) */
	glTranslated(0.0, 0.0, -5.0);

	box->draw(true, true);

	glutSolidCube(1.0);
}