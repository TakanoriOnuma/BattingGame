#include <iostream>

#include "ExecuteScene.h"
#include "OpenGL.h"
#include "AnimationManager.h"


void ExecuteScene::_update()
{
	ExecuteScene::getExecuteScene().update();
}

// AnimationManager���g���Ă���Ԃ͂���Ȃ��q
void ExecuteScene::_display()
{
	ExecuteScene::getExecuteScene().display();
}

// �V���O���g���Ȃ�ł͂̊֐��|�C���^�̃Z�b�g
ExecuteScene::ExecuteScene()
	: scene(NULL)
{
	glutDisplayFunc(ExecuteScene::_display);
	AnimationManager::getAnimationManager().useAnimation(30);		// �����ŏ����ׂ����͔���
	AnimationManager::getAnimationManager().setAnimation(this);
}

ExecuteScene::~ExecuteScene()
{
	if(scene != NULL){
		delete scene;
	}
}

// �֐��ɓ����ϐ����������ăV���O���g������������
ExecuteScene& ExecuteScene::getExecuteScene()
{
	static ExecuteScene exeScene;
	return exeScene;
}

void ExecuteScene::setScene(IScene* scene)
{
	if(this->scene == NULL){		// scene��NULL(�܂�scene���Z�b�g����Ă��Ȃ�)�Ȃ�
		this->scene = scene;		// scene���Z�b�g
	}
}

void ExecuteScene::update()
{
	IScene* nextScene = scene->update();

	if(nextScene == NULL){			// ���̃V�[�����Ȃ����
		exit(0);					// �I������(scene�̃C���X�^���X�̓f�X�g���N�^�Ŕj������)
	}
	else if(nextScene != scene){	// ���̃V�[���ƈႯ���
		delete scene;				// ���̃V�[����j������
		scene = nextScene;			// ���̃V�[���ɕς���
	}
}

void ExecuteScene::display() const
{
	scene->display();
}