#ifndef ___Class_ArmLeg
#define ___Class_ArmLeg

#include "DrawableObject.h"

class MyBox;

class ArmLeg : public DrawableObject{

	double girth;
	double length;
	MyBox* box1;
	MyBox* box2;

	double vec_r1;			// box1の角速度
	double vec_r2;
	double accel_vec_r1;	// box1の角加速度
	double accel_vec_r2;

protected:
	void draw() const;

public:
	using DrawableObject::draw;

	ArmLeg(GLdouble x = 0.0, GLdouble y = 0.0, GLdouble z = 0.0,
		double girth = 1.0, double length = 1.0);
	~ArmLeg();

/*
	MyBox* getBox1(){
		return box1;
	}
	MyBox* getBox2(){
		return box2;
	}
*/
	double getLength() const{
		return length;
	}
	double getGirth() const{
		return girth;
	}

	void update();

	// --- 各Boxに対する角度の設定 --- //
	void setBox1Angle(double angle);
	void setBox2Angle(double angle);
	void addBox1Angle(double value);
	void addBox2Angle(double value);

	// --- 各Boxに対する角速度、角加速度の設定 --- //
	void setBox1AngleVector(double vec_r){
		vec_r1 = vec_r;
	}
	void setBox2AngleVector(double vec_r){
		vec_r2 = vec_r;
	}
	void setBox1AngleAccelVector(double accel_vec_r){
		accel_vec_r1 = accel_vec_r;
	}
	void setBox2AngleAccelVector(double accel_vec_r){
		accel_vec_r2 = accel_vec_r;
	}
	void resetVector(){
		vec_r1 = 0.0;
		vec_r2 = 0.0;
		accel_vec_r1 = 0.0;
		accel_vec_r2 = 0.0;
	}
	void inverseBox1AngleVector(){
		vec_r1 *= -1;
	}
	void inverseBox2AngleVector(){
		vec_r2 *= -1;
	}
};

#endif