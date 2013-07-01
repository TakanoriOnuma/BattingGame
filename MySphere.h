#ifndef ___Class_MySphere
#define ___Class_MySphere

#include "DrawableObject.h"
#include "QuadricObject.h"


class MySphere : public DrawableObject{
	QuadricObject quadObject;

	double radius;		// îºåa
	int    sides;		// ï™äÑêî

	void init();

protected:
	void draw() const;

public:
	using DrawableObject::draw;
	MySphere(double radius = 1.0, int sides = 16);
	MySphere(double x, double y, double z, double radius = 1.0, int sides = 16);

};


#endif