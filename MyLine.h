#ifndef ___Class_MyLine
#define ___Class_MyLine

#include "DrawableObject.h"

class MyLine : public DrawableObject{
	Point3d pt2;		// pt1‚ÍDrawableObject‚ª‚Á‚Ä‚¢‚é

protected:
	void draw() const override;

public:
	using DrawableObject::draw;

	MyLine(double x2, double y2, double z2);
	MyLine(double x, double y, double z, double x2, double y2, double z2);

	void setPoint2(double x2, double y2, double z2){
		pt2.x = x2;
		pt2.y = y2;
		pt2.z = z2;
	}
};

#endif