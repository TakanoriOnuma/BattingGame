#ifndef ___Struct_Color
#define ___Struct_Color

struct ColorData{
	double red;
	double green;
	double blue;
	double alpha;

	ColorData(double red = 0.0, double green = 0.0, double blue = 0.0, double alpha = 1.0)
		: red(red), green(green), blue(blue), alpha(alpha)
	{
	}
};

#endif