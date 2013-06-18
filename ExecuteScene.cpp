#include <iostream>

#include "ExecuteScene.h"
#include "OpenGL.h"
#include "AnimationManager.h"


void ExecuteScene::_update()
{
	ExecuteScene::getExecuteScene().update();
}

// AnimationManagerを使っている間はいらない子
void ExecuteScene::_display()
{
	ExecuteScene::getExecuteScene().display();
}

// シングルトンならではの関数ポインタのセット
ExecuteScene::ExecuteScene()
	: scene(NULL)
{
	glutDisplayFunc(ExecuteScene::_display);
	AnimationManager::getAnimationManager().useAnimation(30);		// ここで書くべきかは微妙
	AnimationManager::getAnimationManager().setAnimation(this);
}

ExecuteScene::~ExecuteScene()
{
	if(scene != NULL){
		delete scene;
	}
}

// 関数に内部変数を持たせてシングルトンを実装する
ExecuteScene& ExecuteScene::getExecuteScene()
{
	static ExecuteScene exeScene;
	return exeScene;
}

void ExecuteScene::setScene(IScene* scene)
{
	if(this->scene == NULL){		// sceneがNULL(まだsceneがセットされていない)なら
		this->scene = scene;		// sceneをセット
	}
}

void ExecuteScene::update()
{
	IScene* nextScene = scene->update();

	if(nextScene == NULL){			// 次のシーンがなければ
		exit(0);					// 終了する(sceneのインスタンスはデストラクタで破棄する)
	}
	else if(nextScene != scene){	// 今のシーンと違ければ
		delete scene;				// 今のシーンを破棄して
		scene = nextScene;			// 次のシーンに変える
	}
}

void ExecuteScene::display() const
{
	scene->display();
}