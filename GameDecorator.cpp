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
	// pauseフラグが立っていない時だけupdateする
	if(!pause_flag){
		IScene* nextScene = game->update();
		if(nextScene != game){		// gameとは違うシーン(NULLか切り替えのシーン)なら
			return nextScene;		// そのシーンを返す
		}
	}

	return this;				// 自分のシーンを返す(継続)
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

	glutSwapBuffers();			// 最後に出力(SceneManager側でしたほうがいいかもしれない)
}