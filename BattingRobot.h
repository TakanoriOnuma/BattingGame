#ifndef ___Class_BattingRobot
#define ___Class_BattingRobot

#include "IBatter.h"
#include "MyRobot.h"

class MyBat;
class MyLine;
class BattingRobot : public MyRobot, public IBatter{

	static const int SWING_FRAME = 10;


	MyBat* bat;

	// 腕の角度変更に対する速度と加速度
	double accel_vec_r;
	double vec_r;
	double accel_vec_r2;
	double vec_r2;

	// 軌跡の移動に対する速度と加速度
	double vec_r_y;
	double vec_r_z;
	double accel_vec_r_y;
	double accel_vec_r_z;

	// 腕の座標変更に対する速度と加速度
	Vector3d accel_vec_dis;
	Vector3d vec_dis;

	Point3d locus;		// 軌跡
	MyLine* line;		// 軌跡の様子を見る

protected:
	// --- Stateクラスの実装クラス --- //
	class Batting;


	void draw() const override;


public:
	using DrawableObject::draw;

	BattingRobot(double x = 0.0, double y = 0.0, double z = 0.0);
	~BattingRobot();

	void update() override;

	void swing() override;

};


#endif