#ifndef ___Class_MySphere
#define ___Class_MySphere

#include "DrawableObject.h"
#include "QuadricObject.h"


class MySphere : public DrawableObject{
	double radius;		// ���a
	int    sides;		// ������

	void init();

protected:
	QuadricObject quadObject;

	virtual void draw() const;

public:
	using DrawableObject::draw;
	MySphere(double radius = 1.0, int sides = 16);
	MySphere(double x, double y, double z, double radius = 1.0, int sides = 16);

	virtual ~MySphere(){ }

	double getRadius() const{
		return radius;
	}
};


#endif