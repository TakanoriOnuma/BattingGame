#ifndef ___Class_AnimationManager
#define ___Class_AnimationManager

#include <list>

class IAnimation;
class AnimationManager{
	std::list<IAnimation*> animations;
	unsigned int frame_rate;

	static void timer(int t);		// ƒ‹[ƒv–ˆ‚Éˆ—‚·‚éŠÖ”

	AnimationManager();
	AnimationManager(const AnimationManager&);
public:
	~AnimationManager();

	static AnimationManager& getAnimationManager();
	static void useAnimation(unsigned int frame_rate = 30);

	void setFrameRate(unsigned int frame_rate){
		this->frame_rate = frame_rate;
	}
	unsigned int getFrameRate() const{
		return frame_rate;
	}

	void setAnimation(IAnimation* animation);
	void removeAnimation(IAnimation* animation);

	void update() const;
};


#endif