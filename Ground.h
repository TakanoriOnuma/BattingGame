#ifndef ___Class_Ground
#define ___Class_Ground

#include "DrawObject.h"

class Ground : public DrawObject{
	static const float ground[2][4];
	int width;
	int distance;

protected:
	void draw() const override;

public:
	using DrawObject::draw;

	Ground(int width = 10, int distance = 10);
	Ground(double x, double y, double z, int width = 10, int distance = 10);

};

#endif