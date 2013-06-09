#ifndef ___Class_MyCylinder
#define ___Class_MyCylinder

#include "DrawObject.h"
#include "QuadricObject.h"


class MyCylinder : public DrawObject{
	QuadricObject quadObject;

	double radius;		// ���a
	double height;		// ����
	int    sides;		// �~�̕����`�搔

	void init();		// ������

protected:
	void draw() const;

public:
	using DrawObject::draw;
	MyCylinder(double radius = 1.0, double height = 1.0, int sides = 16);
	MyCylinder(double x, double y, double z, double radius = 1.0, double height = 1.0, int sides = 16);

};


#endif