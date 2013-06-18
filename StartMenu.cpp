#include "StartMenu.h"
#include "MyTeapot.h"
#include "MaterialData.h"
#include "Game.h"
#include "KeyboardManager.h"

StartMenu::StartMenu()
	: angle_xz(0.0), angle_yz(0.0)
{
	teapot = new MyTeapot();
	teapot->setMaterialData(MaterialData::createMaterialData(Jewel::RUBY));
}

StartMenu::~StartMenu()
{
	delete teapot;
}

void StartMenu::check_char_key()
{
	KeyboardManager& keyboardManager = KeyboardManager::getKeyboardManager();

	if(keyboardManager.isPushCharKey('a')){
		teapot->setMaterialData(MaterialData::createMaterialData(Jewel::EMERALD));
	}
	else if(keyboardManager.isPushCharKey('s')){
		teapot->setMaterialData(MaterialData::createMaterialData(Jewel::JADE));
	}
	else if(keyboardManager.isPushCharKey('d')){
		teapot->setMaterialData(MaterialData::createMaterialData(Jewel::OBSIDIAN));
	}
	else if(keyboardManager.isPushCharKey('f')){
		teapot->setMaterialData(MaterialData::createMaterialData(Jewel::PEARL));
	}
	else if(keyboardManager.isPushCharKey('g')){
		teapot->setMaterialData(MaterialData::createMaterialData(Jewel::RUBY));
	}
	else if(keyboardManager.isPushCharKey('h')){
		teapot->setMaterialData(MaterialData::createMaterialData(Jewel::TURQUOISE));
	}
}

void StartMenu::check_special_key()
{
	KeyboardManager& keyboardManager = KeyboardManager::getKeyboardManager();

	if(keyboardManager.isPushSpecialKey(SpecialKey::LEFT)){
		angle_xz -= 2.0;
	}
	else if(keyboardManager.isPushSpecialKey(SpecialKey::RIGHT)){
		angle_xz += 2.0;
	}

	if(keyboardManager.isPushSpecialKey(SpecialKey::UP)){
		angle_yz -= 2.0;
	}
	else if(keyboardManager.isPushSpecialKey(SpecialKey::DOWN)){
		angle_yz += 2.0;
	}
}

IScene* StartMenu::update()
{
	check_char_key();
	check_special_key();

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
	glRotated(angle_xz, 0.0, 1.0, 0.0);
	glRotated(angle_yz, 1.0, 0.0, 0.0);

	/* 光源の位置を指定 */
	glLightfv(GL_LIGHT0, GL_POSITION, lightpos0);
	glLightfv(GL_LIGHT1, GL_POSITION, lightpos1);

	teapot->draw(true, true);

	glutSwapBuffers();
}