#ifndef ___Class_MyBox
#define ___Class_MyBox

#include "DrawableObject.h"
#include "MyPoint.h"

class MyBox : public DrawableObject{

	static int face[6][4];
	static double normal[6][3];
	double vertex[8][3];

	double length;
	double width;
	double height;

	void init();		// èâä˙âª

protected:
	void draw() const;

public:
	using DrawableObject::draw;

	MyBox(const Point3d& pt, double length = 1.0, double width = 1.0, double height = 1.0);
	MyBox(double x = 0.0, double y = 0.0, double z = 0.0, double length = 1.0, double width = 1.0,
		double height = 1.0);

};


#endif