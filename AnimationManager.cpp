#include "OpenGL.h"

#include "AnimationManager.h"
#include "IAnimation.h"

using namespace std;

AnimationManager::AnimationManager()
	: animations(), frame_rate(30)
{
}

// AnimationManager�ɂ͔j���̐ӔC�͕���Ȃ�
// list�̔j����list�̃f�X�g���N�^�ɂ�点��
AnimationManager::~AnimationManager()
{
}

// �֐��ɓ����ϐ����������ăV���O���g������������
AnimationManager& AnimationManager::getAnimationManager()
{
	static AnimationManager animationManager;
	return animationManager;
}

// TimerFunc�ɃZ�b�g����
void AnimationManager::useAnimation(unsigned int frame_rate)
{
	AnimationManager& animationManager = AnimationManager::getAnimationManager();
	animationManager.frame_rate = frame_rate;
	glutTimerFunc(0, AnimationManager::timer, 1000 / frame_rate);
}

void AnimationManager::setAnimation(IAnimation* animation)
{
	// ���ɓo�^����Ă��邩���ׂ�
	list<IAnimation*>::iterator pos = find(animations.begin(), animations.end(), animation);

	if(pos == animations.end()){			// �o�^����ĂȂ����
		animations.push_back(animation);	// �o�^����
	}
}

void AnimationManager::removeAnimation(IAnimation* animation)
{
	animations.remove(animation);		// �j���̐ӔC���Ȃ����߂����o�^����O������
}

void AnimationManager::update() const
{
	for each (IAnimation* animation in animations)
	{
		animation->update();
	}
}

void AnimationManager::timer(int t)
{
	AnimationManager& animationManager = AnimationManager::getAnimationManager();
	animationManager.update();

	glutPostRedisplay();

	// ���̎g���������������s��
	// ����t�̓^�C�}�[ID��n���̂�������Ȃ�
	glutTimerFunc(t, AnimationManager::timer, t);
}