#include "OpenGL.h"

#include "AnimationManager.h"
#include "IAnimation.h"

using namespace std;

AnimationManager::AnimationManager()
	: animations(), frame_rate(0), time(0)
{
}

// AnimationManager‚É‚Í”jŠü‚ÌÓ”C‚Í•‰‚í‚È‚¢
// list‚Ì”jŠü‚Ílist‚ÌƒfƒXƒgƒ‰ƒNƒ^‚É‚â‚ç‚¹‚é
AnimationManager::~AnimationManager()
{
}

// ŠÖ”‚É“à•”•Ï”‚ğ‚½‚¹‚ÄƒVƒ“ƒOƒ‹ƒgƒ“‚ğÀ‘•‚·‚é
AnimationManager& AnimationManager::getInstance()
{
	static AnimationManager animationManager;
	return animationManager;
}

// TimerFunc‚ÉƒZƒbƒg‚·‚é
void AnimationManager::useAnimation(unsigned int frame_rate)
{
	AnimationManager& animationManager = AnimationManager::getInstance();
	animationManager.setFrameRate(frame_rate);
	glutTimerFunc(animationManager.time, AnimationManager::timer, 0);
}

void AnimationManager::setAnimation(IAnimation* animation)
{
	// Šù‚É“o˜^‚³‚ê‚Ä‚¢‚é‚©’²‚×‚é
	list<IAnimation*>::iterator pos = find(animations.begin(), animations.end(), animation);

	if(pos == animations.end()){			// “o˜^‚³‚ê‚Ä‚È‚¯‚ê‚Î
		animations.push_back(animation);	// “o˜^‚·‚é
	}
}

void AnimationManager::removeAnimation(IAnimation* animation)
{
	animations.remove(animation);		// ”jŠü‚ÌÓ”C‚ª‚È‚¢‚½‚ß‚½‚¾“o˜^‚©‚çŠO‚·‚¾‚¯
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