#include "OpenGL.h"

#include "Camera.h"

Camera::Camera()
	: eye(0.0, 0.0, 1.0), target(0.0, 0.0, 0.0), upVector(0.0, 1.0, 0.0), distance(1.0)
{
}

// eye�̍��W��ύX���邱�ƂŖ����𖳂���
void Camera::adjust()
{


}

void Camera::setCamera() const
{
	gluLookAt(eye.x, eye.y, eye.z,
		target.x, target.y, target.z,
		upVector.x, upVector.y, upVector.z);
}