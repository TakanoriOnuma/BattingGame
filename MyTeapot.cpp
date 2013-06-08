#include "OpenGL.h"
#include "MyTeapot.h"

MyTeapot::MyTeapot(double x, double y, double z, double size)
	: DrawObject(x, y, z), size(size)
{
}

void MyTeapot::draw() const
{
	glScalef(1.0, 1.0, -1.0);		// useShelter���K�v�ɂȂ邩������Ȃ�
	glutSolidTeapot(size);

}