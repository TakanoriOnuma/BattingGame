#ifndef ___Class_MyRobot
#define ___Class_MyRobot

#include "DrawObject.h"
#include "IAnimation.h"

class MyBox;
class ArmLeg;

class MyRobot : public DrawObject, public IAnimation{
	/* ロボットの状態 */
	enum class State;
	State   state;			// 自分の状態

	static const int WALKING_FRAME = 50;		// 歩く動作に必要なフレーム数
	static const int RUNNING_FRAME = 40;		// 走る動作に必要なフレーム数

	Vector3d vec;			// 移行状態で移動する量
	int direction;			// 方向(1か-1で方向を切り替える)

	void setRectBox();

	void (MyRobot::*update_function)();		// update用関数

protected:
	int frame;				// 現在のフレーム数
	struct BodyParts;		// 体の部位の構造体
	BodyParts* bodyParts;	// 体のパーツを持つ

	virtual void draw() const;

	void _walk_init();		// 歩く具体的な初期化
	void _walk();			// 歩く具体的な運動
	void _run_init();		// 走る具体的な初期化
	void _run();			// 走る具体的な運動

public:
	using DrawObject::draw;

	MyRobot(double x = 0.0, double y = 0.0, double z = 0.0);
	virtual ~MyRobot();

	virtual void update() override;

	void stand();
	void run();
	void sit();
	void jump();
	void walk();
};


#endif