#include "GameDecorator.h"
#include "Game.h"
#include "Camera.h"
#include "KeyboardListener.h"
#include "KeyboardManager.h"

static void drawString(const char* str)
{
	while(*str != '\0'){
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *str);
		++str;
	}
}

class GameDecorator::GameDecoratorKeyboardListener : public KeyboardListener
{
	GameDecorator& parent;

public:
	GameDecoratorKeyboardListener(GameDecorator& parent) : parent(parent)
	{
		KeyboardManager::getInstance().addListener(this);
	}
	~GameDecoratorKeyboardListener()
	{
		KeyboardManager::getInstance().removeListener(this);
	}

	void keyboard(unsigned char key, int x, int y) override
	{
		if(key == 'p'){
			parent.pause_flag = !parent.pause_flag;		// フラグを反転させる
		}
	}

	void keyboardUp(unsigned char key, int x, int y) override
	{
	}
	void specialKeyboard(int key, int x, int y) override
	{
	}
	void specialKeyboardUp(int key, int x, int y) override
	{
	}
};

GameDecorator::GameDecorator()
{
	pause_flag = false;
	game = new Game();
	keyboardListener = new GameDecoratorKeyboardListener(*this);
}

GameDecorator::~GameDecorator()
{
	delete game;
	delete keyboardListener;
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