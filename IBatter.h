#ifndef ___Class_IBatter
#define ___Class_IBatter

#include "MyPoint.h"

class IBatter{

public:
	virtual ~IBatter(){ }
	virtual void swing(const Point3d& target) = 0;
};

#endif