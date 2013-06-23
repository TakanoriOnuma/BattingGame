#include "OpenGL.h"

#include "Camera.h"
#include "TriFunction.h"

#include <iostream>

using namespace std;

Camera::Camera()
	: eye(0.0, 0.0, 10.0), target(0.0, 0.0, 0.0), upVector(0.0, 1.0, 0.0),
	distance(10.0), angle_xz(90.0), angle_yz(0.0)
{
}

// eye‚ÌÀ•W‚ğ•ÏX‚·‚é‚±‚Æ‚Å–µ‚‚ğ–³‚­‚·
void Camera::adjust()
{
	TriFunction& tri_func = TriFunction::Instance();
	eye.x = distance * tri_func.t_cos((int)angle_yz) * tri_func.t_cos((int)angle_xz);
	eye.y = distance * tri_func.t_sin((int)angle_yz);
	eye.z = distance * tri_func.t_cos((int)angle_yz) * tri_func.t_sin((int)angle_xz);
}

void Camera::setCamera() const
{
	gluLookAt(eye.x, eye.y, eye.z,
		target.x, target.y, target.z,
		upVector.x, upVector.y, upVector.z);
}