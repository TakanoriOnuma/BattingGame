#include "SceneManager.h"
#include "OpenGL.h"
#include "AnimationManager.h"


void SceneManager::_update()
{
	SceneManager::getInstance().update();
}

// AnimationManagerを使っている間はいらない子
void SceneManager::_display()
{
	SceneManager::getInstance().display();
}

// シングルトンならではの関数ポインタのセット
SceneManager::SceneManager()
	: scene(NULL)
{
}

SceneManager::~SceneManager()
{
	if(scene != NULL){
		delete scene;
	}
}

// 関数に内部変数を持たせてシングルトンを実装する
SceneManager& SceneManager::getInstance()
{
	static SceneManager exeScene;
	return exeScene;
}

void SceneManager::setScene(IScene* scene)
{
	if(this->scene == NULL){		// sceneがNULL(まだsceneがセットされていない)なら
		this->scene = scene;		// sceneをセット

		// callback 関数をセット
		glutDisplayFunc(SceneManager::_display);
		AnimationManager::getInstance().useAnimation(30);		// ここで書くべきかは微妙
		AnimationManager::getInstance().setAnimation(this);
	}
}

void SceneManager::update()
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

void SceneManager::display() const
{
	scene->display();
}