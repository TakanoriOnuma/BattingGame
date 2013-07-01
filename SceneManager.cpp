#include <iostream>

#include "SceneManager.h"
#include "OpenGL.h"
#include "AnimationManager.h"


void SceneManager::_update()
{
	SceneManager::getSceneManager().update();
}

// AnimationManager���g���Ă���Ԃ͂���Ȃ��q
void SceneManager::_display()
{
	SceneManager::getSceneManager().display();
}

// �V���O���g���Ȃ�ł͂̊֐��|�C���^�̃Z�b�g
SceneManager::SceneManager()
	: scene(NULL)
{
	std::cout << "create SceneManager" << std::endl;
	glutDisplayFunc(SceneManager::_display);
	AnimationManager::getAnimationManager().useAnimation(30);		// �����ŏ����ׂ����͔���
	AnimationManager::getAnimationManager().setAnimation(this);
}

SceneManager::~SceneManager()
{
	std::cout << "delete SceneManager" << std::endl;
	if(scene != NULL){
		delete scene;
	}
}

// �֐��ɓ����ϐ����������ăV���O���g������������
SceneManager& SceneManager::getSceneManager()
{
	static SceneManager exeScene;
	return exeScene;
}

void SceneManager::setScene(IScene* scene)
{
	if(this->scene == NULL){		// scene��NULL(�܂�scene���Z�b�g����Ă��Ȃ�)�Ȃ�
		this->scene = scene;		// scene���Z�b�g
	}
}

void SceneManager::update()
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

void SceneManager::display() const
{
	scene->display();
}