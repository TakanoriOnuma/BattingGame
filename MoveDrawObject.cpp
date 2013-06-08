#include "MoveDrawObject.h"
#include "DrawObject.h"
#include "MyVector.h"

struct MoveDrawObject::MoveData{
	Vector3d vec;			// •¨‘Ì‚»‚Ì‚à‚Ì‚ÌˆÚ“®—Ê
	Vector3d accel_vec;		// vec‚É‘Î‚·‚é‰Á‘¬“x
	double   vec_r;			// Šp“x‚É‘Î‚·‚éŠp‘¬“x
	double   accel_vec_r;	// vec_r‚É‘Î‚·‚éŠp‰Á‘¬“x
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