#include "StartMenu.h"
#include "MyTeapot.h"
#include "MaterialData.h"
#include "Game.h"
#include "KeyboardManager.h"

StartMenu::StartMenu()
{
	teapot = new MyTeapot();
	teapot->setMaterialData(MaterialData::createMaterialData(Jewel::RUBY));
}

StartMenu::~StartMenu()
{
	delete teapot;
}

IScene* StartMenu::update()
{
	if(KeyboardManager::getKeyboardManager().isPushCharKey(' ')){
		return new Game();
	}

	return this;
}

void StartMenu::display() const
{
	static GLfloat lightpos0[] = { 3.0, 4.0, 5.0, 1.0 };
	static GLfloat lightpos1[] = {-3.0, 4.0, 5.0, 1.0 };
	/* 画面クリア */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/* モデル・ビュー変換行列の初期化 */
	glLoadIdentity();

	/* 視点の移動(物体の方を奥に移す) */
	glTranslated(0.0, 0.0, -13.0);

	/* 光源の位置を指定 */
	glLightfv(GL_LIGHT0, GL_POSITION, lightpos0);
	glLightfv(GL_LIGHT1, GL_POSITION, lightpos1);

	teapot->draw(true, true);

	glutSwapBuffers();
}