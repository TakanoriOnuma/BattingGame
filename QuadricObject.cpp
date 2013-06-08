#include "OpenGL.h"

#include "QuadricObject.h"

// http://msdn.microsoft.com/ja-jp/library/windows/desktop/dd368665(v=vs.85).aspx

QuadricObject::QuadricObject()
{
	quad = gluNewQuadric();
}

QuadricObject::~QuadricObject()
{
	gluDeleteQuadric(quad);
}