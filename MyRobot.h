#ifndef ___Class_MyRobot
#define ___Class_MyRobot

#include "DrawObject.h"

class MyBox;
class ArmLeg;

class MyRobot : public DrawObject{
	/* ロボットの状態 */
	enum class State;



	/* どっち足を前に出すか */
/*
	enum WalkLeg{
		LEFT,			// 左
		RIGHT,			// 右

		SIZE,			// enumのサイズ
	};
*/
	static const int WALKING_FRAME = 50;		// 歩く動作に必要なフレーム数
	static const int RUNNING_FRAME = 40;		// 走る動作に必要なフレーム数



	State   state;			// 自分の状態
//	WalkLeg leg;			// どっち足を前に出すか

	struct MoveData;		// フレームごとの動作に使う移動データの構造体
	Vector3d vec;			// 移行状態で移動する量
	int direction;			// 方向(1か-1で方向を切り替える)

/*
	double   vec_r1;		// 移行状態で回転するr1
	double   arm_vec_r21;	// 移行状態で腕が回転するr21
	double   arm_vec_r22;	// 移行状態で腕が回転するr22
	double   leg_vec_r21;	// 移行状態で足が回転するr21
	double   leg_vec_r22;	// 移行状態で足が回転するr22
*/
	void setRectBox();

	void (MyRobot::*update_function)();		// update用関数

protected:
	int frame;				// 現在のフレーム数
	struct BodyParts;		// 体の部位の構造体
	BodyParts* bodyParts;	// 体のパーツを持つ

	void draw() const;

	void _walk_init();		// 歩く具体的な初期化
	void _walk();			// 歩く具体的な運動
	void _run_init();		// 走る具体的な初期化
	void _run();			// 走る具体的な運動

public:
	using DrawObject::draw;

	MyRobot(double x = 0.0, double y = 0.0, double z = 0.0);
	virtual ~MyRobot();

	virtual void update();

	void stand();
	void run();
	void sit();
	void jump();
	void walk();
};


#endif