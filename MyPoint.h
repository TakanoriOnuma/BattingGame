#ifndef ___Struct_MyPoint
#define ___Struct_MyPoint

#include "MyVector.h"

template<class T>
struct Point3{
	T x;
	T y;
	T z;

	Point3(T x = 0, T y = 0, T z = 0) : x(x), y(y), z(z)
	{
	}

	~Point3(){ }

	// ìØÇ∂å^Ç∂Ç·Ç»Ç¢Ç∆èoóàÇ»Ç¢
	void move(const Vector3<T>& vec)
	{
		this->x += vec.x;
		this->y += vec.y;
		this->z += vec.z;
	}
};

struct Point3d : public Point3<double>
{
	Point3d(double x = 0, double y = 0, double z = 0) : Point3(x, y, z)
	{
	}
};




template<class T>
struct Point2{
	T x;
	T y;

	Point2(T x = 0, T y = 0) : x(x), y(y)
	{
	}

	~Point2(){ }

	// ìØÇ∂å^Ç∂Ç·Ç»Ç¢Ç∆èoóàÇ»Ç¢
	void move(const Vector3<T>& vec)
	{
		this->x += vec.x;
		this->y += vec.y;
	}
};

struct Point2i : public Point2<int>
{
	Point2i(int x = 0, int y = 0) : Point2(x, y)
	{
	}
};

#endif