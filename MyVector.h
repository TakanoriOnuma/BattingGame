#ifndef ___Struct_Vector
#define ___Struct_Vector

#include "OpenGL.h"

template<class T>
struct Vector3{
	T x;
	T y;
	T z;

	Vector3(T x = 0, T y = 0, T z = 0) : x(x), y(y), z(z)
	{
	}

	~Vector3(){ }

	Vector3& operator += (const Vector3& vec){
		this->x += vec.x;
		this->y += vec.y;
		this->z += vec.z;
		return *this;
	}
};

struct Vector3d : public Vector3<GLdouble>
{
	Vector3d(GLdouble x = 0, GLdouble y = 0, GLdouble z = 0) : Vector3(x, y, z)
	{
	}
};



template<class T>
struct Vector2{
	T x;
	T y;

	Vector2(T x = 0, T y = 0) : x(x), y(y)
	{
	}

	~Vector2(){ }

};

struct Vector2d : public Vector2<GLdouble>
{
	Vector2d(GLdouble x = 0, GLdouble y = 0) : Vector2(x, y)
	{
	}
};

#endif