#ifndef ___Class_Camera
#define ___Class_Camera

#include "MyPoint.h"
#include "MyVector.h"

class Camera{
	Point3d  eye;			// 視点の座標
	Point3d  target;		// 注視点の座標
	Vector3d upVector;		// 上のベクトル
	double   distance;		// eyeとtargetとの距離
	double   angle_xz;		// xz平面に対する角度
	double   angle_yz;		// yz平面に対する角度

	void adjust();			// 変更に矛盾が内容に調整する

	static void adj_degree(double& degree){
		while(degree < 0){
			degree += 360;
		}
		while(degree >= 360){
			degree -= 360;
		}
	}
public:
	Camera();
//	Camera(const Point3d& eye, const Point3d& target, const Vector3d& upVector);

	void setCamera() const;

	// === 各メンバの変更と調整 === //
	void addAngle_xz(double value){
		angle_xz += value;
		adj_degree(angle_xz);
		adjust();
	}
	void addAngle_yz(double value){
		angle_yz += value;
		if(angle_yz <= -90.0){
			angle_yz = -89.0;
		}
		else if(angle_yz > 90.0){
			angle_yz = 90.0;
		}
		adjust();
	}
	void addDistance(double value){
		distance += value;
		if(distance < 1.0){
			distance = 1.0;
		}
		adjust();
	}

	void setAngle_xz(double angle){
		angle_xz = angle;
		adj_degree(angle_xz);
		adjust();
	}
	void setAngle_yz(double angle){
		angle_yz = angle;
		if(angle_yz <= -90.0){
			angle_yz = -89.0;
		}
		else if(angle_yz > 90.0){
			angle_yz = 90.0;
		}
		adjust();
	}
	void setDistance(double distance){
		this->distance = distance;
		if(this->distance < 1.0){
			this->distance = 1.0;
		}
		adjust();
	}

	double getAngle_xz() const{
		return angle_xz;
	}
	double getAngle_yz() const{
		return angle_yz;
	}
	double getDistance() const{
		return distance;
	}

	// 意図的にいじる
	Point3d& getEye(){
		return eye;
	}
	Point3d& getTarget(){
		return target;
	}
};

#endif