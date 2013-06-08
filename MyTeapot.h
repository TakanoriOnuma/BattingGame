#ifndef ___Class_MyTeapot
#define ___Class_MyTeapot

#include "DrawObject.h"

class MyTeapot : public DrawObject{
	double size;

protected:
	void draw() const;

public:
	using DrawObject::draw;

	MyTeapot(double x = 0.0, double y = 0.0, double z = 0.0, double size = 1.0);

};


#endif