#ifndef ___Class_MyBat
#define ___Class_MyBat

#include "DrawObject.h"
#include "QuadricObject.h"

class MyBat : public DrawObject{
	QuadricObject quadObject;

	void init();

protected:
	void draw() const;

public:
	using DrawObject::draw;

	MyBat(double x = 0.0, double y = 0.0, double z = 0.0);
	MyBat(const Point3d& pt);

};


#endif