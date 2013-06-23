#ifndef ___Class_Camera
#define ___Class_Camera

#include "MyPoint.h"
#include "MyVector.h"

class Camera{
	Point3d  eye;			// ���_�̍��W
	Point3d  target;		// �����_�̍��W
	Vector3d upVector;		// ��̃x�N�g��
	double   distance;		// eye��target�Ƃ̋���
	double   angle_xz;		// xz���ʂɑ΂���p�x
	double   angle_yz;		// yz���ʂɑ΂���p�x

	void adjust();			// �ύX�ɖ��������e�ɒ�������

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

	// === �e�����o�̕ύX�ƒ��� === //
	void addAngle_xz(double value){
		angle_xz += value;
		adj_degree(angle_xz);
		adjust();
	}
	void addAngle_yz(double value){
		angle_yz += value;
		adj_degree(angle_yz);
		adjust();
	}
	void addDistance(double value){
		distance += value;
		adjust();
	}

	// �Ӑ}�I�ɂ�����
	Point3d& getEye(){
		return eye;
	}
	Point3d& getTarget(){
		return target;
	}
};

#endif