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
	/* ��ʃN���A */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/* ���f���E�r���[�ϊ��s��̏����� */
	glLoadIdentity();

	/* ���_�̈ړ�(���̂̕������Ɉڂ�) */
	glTranslated(0.0, 0.0, -13.0);

	/* �����̈ʒu���w�� */
	glLightfv(GL_LIGHT0, GL_POSITION, lightpos0);
	glLightfv(GL_LIGHT1, GL_POSITION, lightpos1);

	teapot->draw(true, true);

	glutSwapBuffers();
}