#ifndef ___Class_RectangularParallelepiped
#define ___Class_RectangularParallelepiped

// ===== ’¼•û‘ÌƒNƒ‰ƒX ===== //
class RectangularParallelepiped{

public:
	double length;
	double width;
	double height;

	RectangularParallelepiped();
	RectangularParallelepiped(double length, double width, double height);

	void setRectangularParallelepiped(double length, double width, double height){
		this->length = length;
		this->width = width;
		this->height = height;
	}
};

#endif