#include "MoveDrawObject.h"
#include "DrawObject.h"
#include "MyVector.h"

struct MoveDrawObject::MoveData{
	Vector3d vec;			// 物体そのものの移動量
	Vector3d accel_vec;		// vecに対する加速度
	double   vec_r;			// 角度に対する角速度
	double   accel_vec_r;	// vec_rに対する角加速度
};

MoveDrawObject::MoveDrawObject(DrawObject* drawObject)
	: drawObject(drawObject)
{
	moveData = new MoveData();
}

MoveDrawObject::~MoveDrawObject()
{
	delete moveData;
}

void MoveDrawObject::update()
{
	drawObject->move(moveData->vec);
	moveData->vec += moveData->accel_vec;
	drawObject->addAngle(moveData->vec_r);
	moveData->vec_r += moveData->accel_vec_r;
}

void MoveDrawObject::setVector(const Vector3d& vec)
{
	moveData->vec = vec;
}

void MoveDrawObject::setVector(double x, double y, double z)
{
	Vector3d& vec = moveData->vec;
	vec.x = x;
	vec.y = y;
	vec.z = z;
}

void MoveDrawObject::setAccelVector(const Vector3d& accel_vec)
{
	moveData->accel_vec = accel_vec;
}

void MoveDrawObject::setAccelVector(double x, double y, double z)
{
	Vector3d& accel_vec = moveData->accel_vec;
	accel_vec.x = x;
	accel_vec.y = y;
	accel_vec.z = z;
}

void MoveDrawObject::setAngleVector(double vec_r)
{
	moveData->vec_r = vec_r;
}

void MoveDrawObject::setAccelAngleVector(double accel_vec_r)
{
	moveData->accel_vec_r = accel_vec_r;
}