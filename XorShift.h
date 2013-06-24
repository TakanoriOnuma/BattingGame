#ifndef ___Class_XorShift
#define ___Class_XorShift

class XorShift
{
	unsigned int x;
	unsigned int y;
	unsigned int z;
	unsigned int w;

	// コンストラクタ
	XorShift(unsigned int w = 88675123);
	XorShift(const XorShift&);
public:
	static XorShift& instance();

	void setSeed(unsigned int seed);

	unsigned int rand();
	void debug();
};


#endif