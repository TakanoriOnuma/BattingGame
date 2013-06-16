#ifndef ___Class_AnimationManager
#define ___Class_AnimationManager

#include <list>

class IAnimation;
class AnimationManager{
	std::list<IAnimation*> animations;
	unsigned int frame_rate;		// 1秒に何フレーム描画するか
	unsigned int time;				// 何ミリ秒のインターバルか

	static void timer(int t);		// ループ毎に処理する関数

	AnimationManager();
	AnimationManager(const AnimationManager&);
public:
	~AnimationManager();

	static AnimationManager& getAnimationManager();
	static void useAnimation(unsigned int frame_rate = 30);

	void setFrameRate(unsigned int frame_rate){
		this->frame_rate = frame_rate;
		this->time = 1000 / frame_rate;
	}
	unsigned int getFrameRate() const{
		return frame_rate;
	}

	void setAnimation(IAnimation* animation);
	void removeAnimation(IAnimation* animation);

	void update() const;
};


#endif