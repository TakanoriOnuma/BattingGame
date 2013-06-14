#include "OpenGL.h"
#include "MyTeapot.h"

MyTeapot::MyTeapot(double x, double y, double z, double size)
	: DrawObject(x, y, z), size(size)
{
	// Teapotのサイズは検討がつかないため、rectBoxは初期化しない
}

void MyTeapot::draw() const
{
	glScalef(1.0, 1.0, -1.0);		// useShelterが必要になるかもしれない
	glutSolidTeapot(size);

}