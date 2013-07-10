#ifndef ___Class_Rectangle2D
#define ___Class_Rectangle2D

#include "DrawableObject.h"
#include "ColorData.h"

class Rectangle2D : public DrawableObject{
	double width;
	double height;
	ColorData color;

protected:
	void draw() const override;

public:
	using DrawableObject::draw;

	Rectangle2D(double width = 1.0, double height = 1.0);
	Rectangle2D(double width, double height, const ColorData& color);
	Rectangle2D(double x, double y, double z, double width, double height, const ColorData& color);

	double getWidth() const{
		return width;
	}
	double getHeight() const{
		return height;
	}

	void drawField() const;
};

#endif