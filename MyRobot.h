#ifndef ___Class_MyRobot
#define ___Class_MyRobot

#include "DrawableObject.h"
#include "IAnimation.h"

class MyBox;
class ArmLeg;

class MyRobot : public DrawableObject, public IAnimation{
	/* ロボットの状態 */
	enum class Condition;
	Condition condition;			// 自分の状態

	static const int WALKING_FRAME = 50;		// 歩く動作に必要なフレーム数
	static const int RUNNING_FRAME = 40;		// 走る動作に必要なフレーム数

	Vector3d vec;			// 移行状態で移動する量
	int direction;			// 方向(1か-1で方向を切り替える)

	void setRectBox();

	void (MyRobot::*update_function)();		// update用関数

protected:
	// --- デザインパターン State --- //
	class  State;		// Stateクラス
	State* state;

	// --- Stateクラスのサブクラスを前方宣言 --- //
	class Standing;
	class Walking;
	class Running;
	

	int frame;				// 現在のフレーム数
	struct BodyParts;		// 体の部位の構造体
	BodyParts* bodyParts;	// 体のパーツを持つ

	virtual void draw() const;

	void _run_init();		// 走る具体的な初期化
	void _run();			// 走る具体的な運動

public:
	using DrawableObject::draw;

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