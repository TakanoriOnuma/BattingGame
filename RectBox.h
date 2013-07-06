#ifndef ___Class_RectBox
#define ___Class_RectBox

// ===== ’¼•û‘ÌƒNƒ‰ƒX ===== //
class RectBox{
	static const int edge[12][2];

public:
	double length;
	double width;
	double height;

	RectBox();
	RectBox(double length, double width, double height);

	void setRectBox(double length, double width, double height){
		this->length = length;
		this->width = width;
		this->height = height;
	}

	void draw() const;
};

#endif