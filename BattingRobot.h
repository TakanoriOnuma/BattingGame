#ifndef ___Class_BattingRobot
#define ___Class_BattingRobot

#include "IBatter.h"
#include "MyRobot.h"

class MyBat;
class BattingRobot : public MyRobot, public IBatter{



	MyBat* bat;

	// 腕の角度変更に対する速度と加速度
	double accel_vec_r;
	double vec_r;
	double accel_vec_r2;
	double vec_r2;

	// 腕の座標変更に対する速度と加速度
	Vector3d accel_vec_dis;
	Vector3d vec_dis;

	Point3d target;

protected:
	// --- Stateクラスの実装クラス --- //
	class Batting;


	void draw() const override;


public:
	using DrawableObject::draw;

	static const int SWING_FRAME = 30;


	BattingRobot(double x = 0.0, double y = 0.0, double z = 0.0);
	~BattingRobot();

	void update() override;

	void swing(const Point3d& target) override;

	int getFrame() const{
		return frame;
	}
	const Point3d& getTargetPoint() const{
		return target;
	}
};


#endif