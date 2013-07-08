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

			if(parent.pause_flag){			// ポーズフラグがあれば
				parent.game->stop();		// ゲームを止める
			}
			else{							// フラグがなければ
				parent.game->restart();		// ゲームを再開する
			}
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
	camera = new Camera();
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

	glLoadIdentity();			// 一度モデルビューを初期化する
	camera->setCamera();		// カメラをセット

	if(pause_flag){
		glDisable(GL_LIGHTING);
		glColor3d(0.0, 0.0, 0.0);
		glRasterPos3d(-0.4, 0.0, 4.0);

		drawString("PAUSE");
		glEnable(GL_LIGHTING);
	}

	glutSwapBuffers();			// 最後に出力(SceneManager側でしたほうがいいかもしれない)
}