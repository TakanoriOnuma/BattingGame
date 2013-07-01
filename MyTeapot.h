#ifndef ___Class_MyTeapot
#define ___Class_MyTeapot

#include "DrawableObject.h"

class MyTeapot : public DrawableObject{
	double size;

protected:
	void draw() const;

public:
	using DrawableObject::draw;

	MyTeapot(double x = 0.0, double y = 0.0, double z = 0.0, double size = 1.0);

};


#endif