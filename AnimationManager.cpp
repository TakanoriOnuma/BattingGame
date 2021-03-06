#include "OpenGL.h"

#include "AnimationManager.h"
#include "IAnimation.h"

using namespace std;

AnimationManager::AnimationManager()
	: animations(), frame_rate(0), time(0)
{
}

// AnimationManagerには破棄の責任は負わない
// listの破棄はlistのデストラクタにやらせる
AnimationManager::~AnimationManager()
{
}

// 関数に内部変数を持たせてシングルトンを実装する
AnimationManager& AnimationManager::getInstance()
{
	static AnimationManager animationManager;
	return animationManager;
}

// TimerFuncにセットする
void AnimationManager::useAnimation(unsigned int frame_rate)
{
	AnimationManager& animationManager = AnimationManager::getInstance();
	animationManager.setFrameRate(frame_rate);
	glutTimerFunc(animationManager.time, AnimationManager::timer, 0);
}

void AnimationManager::setAnimation(IAnimation* animation)
{
	// 既に登録されているか調べる
	list<IAnimation*>::iterator pos = find(animations.begin(), animations.end(), animation);

	if(pos == animations.end()){			// 登録されてなければ
		animations.push_back(animation);	// 登録する
	}
}

void AnimationManager::removeAnimation(IAnimation* animation)
{
	animations.remove(animation);		// 破棄の責任がないためただ登録から外すだけ
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
	AnimationManager& animationManager = AnimationManager::getInstance();
	animationManager.update();

	glutPostRedisplay();

	glutTimerFunc(animationManager.time, AnimationManager::timer, t);
}