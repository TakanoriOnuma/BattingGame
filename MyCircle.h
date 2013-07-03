#ifndef ___Class_MyCircle
#define ___Class_MyCircle

#include "DrawableObject.h"
#include "ColorData.h"

class MyCircle : public DrawableObject{
	double radius;
	ColorData color;

protected:
	void draw() const override;

public:
	using DrawableObject::draw;

	MyCircle(double radius = 1.0);
	MyCircle(double radius, const ColorData& color);
	MyCircle(double x, double y, double z, double radius, const ColorData& color);
};

#endif