#include "SceneManager.h"
#include "OpenGL.h"
#include "AnimationManager.h"


void SceneManager::_update()
{
	SceneManager::getInstance().update();
}

// AnimationManager���g���Ă���Ԃ͂���Ȃ��q
void SceneManager::_display()
{
	SceneManager::getInstance().display();
}

// �V���O���g���Ȃ�ł͂̊֐��|�C���^�̃Z�b�g
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

// �֐��ɓ����ϐ����������ăV���O���g������������
SceneManager& SceneManager::getInstance()
{
	static SceneManager exeScene;
	return exeScene;
}

void SceneManager::setScene(IScene* scene)
{
	if(this->scene == NULL){		// scene��NULL(�܂�scene���Z�b�g����Ă��Ȃ�)�Ȃ�
		this->scene = scene;		// scene���Z�b�g

		// callback �֐����Z�b�g
		glutDisplayFunc(SceneManager::_display);
		AnimationManager::getInstance().useAnimation(30);		// �����ŏ����ׂ����͔���
		AnimationManager::getInstance().setAnimation(this);
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