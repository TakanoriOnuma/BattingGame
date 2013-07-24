#ifndef ___Class_Ground
#define ___Class_Ground

#include "DrawableObject.h"

class MyLine;
class Ground : public DrawableObject{
	static const float ground[2][4];
	int width;
	int distance;

	MyLine *line1, *line2;

	void init();

protected:
	void draw() const override;

public:
	using DrawableObject::draw;

	Ground(int width = 10, int distance = 10);
	Ground(double x, double y, double z, int width = 10, int distance = 10);

	~Ground();
};

#endif