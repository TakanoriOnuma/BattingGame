#include "TriFunction.h"

#include <cmath>

const double TriFunction::PI = 3.14159265358979323846;

TriFunction::TriFunction()
{
	for(int i = 0; i < 360; i++){
		sin_data[i] = ::sin(DegToRad(i));
		cos_data[i] = ::cos(DegToRad(i));
	}
}

// 関数に内部変数を持たせてシングルトンを実装する
TriFunction& TriFunction::getInstance()
{
	static TriFunction func;
	return func;
}

int TriFunction::adj_degree(int degree)
{
	while(degree < 0){
		degree += 360;
	}
	while(degree >= 360){
		degree -= 360;
	}
	return degree;
}

double TriFunction::t_sin(int degree)
{
	return sin_data[adj_degree(degree)];
}

double TriFunction::t_cos(int degree)
{
	return cos_data[adj_degree(degree)];
}

double TriFunction::t_tan(int degree)
{
	int deg = adj_degree(degree);
	return sin_data[deg] / cos_data[deg];
}


double TriFunction::sin(double degree)
{
	return ::sin(DegToRad(degree));
}

double TriFunction::cos(double degree)
{
	return ::cos(DegToRad(degree));
}

double TriFunction::tan(double degree)
{
	return ::tan(DegToRad(degree));
}