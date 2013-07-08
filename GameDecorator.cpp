#include "GameDecorator.h"
#include "Game.h"
#include "Camera.h"

static void drawString(const char* str)
{
	while(*str != '\0'){
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *str);
		++str;
	}
}

GameDecorator::GameDecorator()
{
	pause_flag = true;
	game = new Game();
}

GameDecorator::~GameDecorator()
{
	delete game;
}

IScene* GameDecorator::update()
{
	// pause�t���O�������Ă��Ȃ�������update����
	if(!pause_flag){
		IScene* nextScene = game->update();
		if(nextScene != game){		// game�Ƃ͈Ⴄ�V�[��(NULL���؂�ւ��̃V�[��)�Ȃ�
			return nextScene;		// ���̃V�[����Ԃ�
		}
	}

	return this;				// �����̃V�[����Ԃ�(�p��)
}

void GameDecorator::display() const
{
	game->display();

	if(pause_flag){
		glDisable(GL_LIGHTING);
		glColor3d(0.0, 0.0, 0.0);
		glRasterPos3d(-0.4, 0.0, 4.0);
		drawString("PAUSE");
		glEnable(GL_LIGHTING);
	}

	glutSwapBuffers();			// �Ō�ɏo��(SceneManager���ł����ق���������������Ȃ�)
}