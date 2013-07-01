#ifndef ___Class_TriFunction
#define ___Class_TriFunction




class TriFunction{
	double sin_data[360];
	double cos_data[360];

	TriFunction();
	TriFunction(const TriFunction&);
	int adj_degree(int degree);
public:
	static const double PI;

	static TriFunction& getInstance();

	double DegToRad(double degree){
		return degree * PI / 180.0;
	}
	double RadToDeg(double radian){
		return 180.0 * radian / PI;
	}

	double t_sin(int degree);
	double t_cos(int degree);
	double t_tan(int degree);

	double sin(double degree);
	double cos(double degree);
	double tan(double degree);
};


#endif