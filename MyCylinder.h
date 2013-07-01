#ifndef ___Class_MyCylinder
#define ___Class_MyCylinder

#include "DrawableObject.h"
#include "QuadricObject.h"


class MyCylinder : public DrawableObject{
	QuadricObject quadObject;

	double radius;		// ”¼Œa
	double height;		// ‚‚³
	int    sides;		// ‰~‚Ì•ªŠ„•`‰æ”

	void init();		// ‰Šú‰»

protected:
	void draw() const;

public:
	using DrawableObject::draw;
	MyCylinder(double radius = 1.0, double height = 1.0, int sides = 16);
	MyCylinder(double x, double y, double z, double radius = 1.0, double height = 1.0, int sides = 16);

};


#endif