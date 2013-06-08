#ifndef ___Class_QuadricObject
#define ___Class_QuadricObject

class GLUquadric;
class QuadricObject{
	GLUquadric* quad;

public:
	QuadricObject();
	~QuadricObject();

	GLUquadric* getQuadric() const{
		return quad;
	}
};

#endif