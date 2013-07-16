#include "GameDecorator.h"
#include "Game.h"
#include "Camera.h"
#include "KeyboardListener.h"
#include "KeyboardManager.h"
#include "RoughHitProcesser.h"
#include "NoDelayHitProcesser.h"

#include <sstream>

using namespace std;

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

	glDisable(GL_LIGHTING);
	glColor3d(1.0, 0.0, 0.0);
	glRasterPos3d(-3.0, 2.2, 0.0);
	drawString("Difficulity:");
	drawString(game->difficulity_str.c_str());

	if(game->hitProcesser == Game::RoughHitProcesser::getInstance()){
		glColor3d(0.0, 1.0, 1.0);
		glRasterPos3d(-3.0, 1.7, 0.0);
		drawString("RoughHitProcesser");
	}
	else if(game->hitProcesser == Game::NoDelayHitProcesser::getInstance()){
		glColor3d(1.0, 0.0, 1.0);
		glRasterPos3d(-3.0, 1.7, 0.0);
		drawString("NoDelayHitProcesser");
	}

	glColor3d(0.5, 0.0, 0.5);
	glRasterPos3d(-3.0, 1.2, 0.0);
	drawString(game->usingDeviceName.c_str());

	// ボールの残りの数を表示
	stringstream stream;
	stream << game->ball_num;
	glColor3d(0.0, 0.0, 1.0);
	glRasterPos3d(1.8, 2.0, 0.0);
	drawString("Ball:");
	drawString(stream.str().c_str());

	// スコアの表示
	stream.str("");		// バッファのクリア
	stream << game->score;
	glColor3d(0.0, 0.0, 1.0);
	glRasterPos3d(1.8, 1.5, 0.0);
	drawString("Score:");
	drawString(stream.str().c_str());

	// 結果の表示
	glColor3d(1.0, 0.0, 1.0);
	glRasterPos3d(1.9, 0.5, 0.0);
	drawString(game->result_str.c_str());

	glEnable(GL_LIGHTING);

	glutSwapBuffers();			// 最後に出力(SceneManager側でしたほうがいいかもしれない)
}