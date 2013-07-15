#ifndef ___Class_MyBat
#define ___Class_MyBat

#include "DrawableObject.h"
#include "QuadricObject.h"

class MyBat : public DrawableObject{
	QuadricObject quadObject;
	unsigned int  texNumber;

	void init();

protected:
	void draw() const;

public:
	using DrawableObject::draw;

	MyBat(double x = 0.0, double y = 0.0, double z = 0.0);
	MyBat(const Point3d& pt);

};


#endif