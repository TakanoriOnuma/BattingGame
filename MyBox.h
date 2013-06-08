#ifndef ___Class_MyBox
#define ___Class_MyBox

#include <gl/glut.h>
#include "DrawObject.h"
#include "MyPoint.h"

class MyBox : public DrawObject{

	static int face[6][4];
	static GLdouble normal[6][3];
	GLdouble vertex[8][3];

	double length;
	double width;
	double height;

	void init();		// èâä˙âª

protected:
	void draw() const;

public:
	using DrawObject::draw;

	MyBox(const Point3d& pt, double length = 1.0, double width = 1.0, double height = 1.0);
	MyBox(GLdouble x = 0.0, GLdouble y = 0.0, GLdouble z = 0.0, double length = 1.0, double width = 1.0,
		double height = 1.0);

};


#endif