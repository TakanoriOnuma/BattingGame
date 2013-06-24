#include <iostream>

#include "XorShift.h"

XorShift::XorShift(unsigned int w)
{
	this->x = 123456789;
	this->y = 362436069;
	this->z = 521288629;
	this->w = w;
}

// 関数に内部変数を持たせてシングルトンを実装する
XorShift& XorShift::instance()
{
	static XorShift xorShift;
	return xorShift;
}

void XorShift::setSeed(unsigned int seed)
{
	this->w = seed;
}

unsigned int XorShift::rand()
{
	unsigned int t = this->x ^ (this->x << 11);

	// x ← y ← z ← w と移動して行っている
	this->x = this->y;
	this->y = this->z;
	this->z = this->w;

	this->w = (this->w ^ (this->w >> 19)) ^ (t ^ (t >> 8));
	return this->w;
}

void XorShift::debug()
{
	std::cout << "x:" << this->x << std::endl;
	std::cout << "y:" << this->y << std::endl;
	std::cout << "z:" << this->z << std::endl;
	std::cout << "w:" << this->w << std::endl;
}