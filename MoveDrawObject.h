#ifndef ___Class_MoveDrawObject
#define ___Class_MoveDrawObject


class DrawObject;
struct Vector3d;
// DrawObjectを簡単に動かせるようにしたクラス
// DrawObjectの破棄は自分で行う
class MoveDrawObject{
	DrawObject* drawObject;

	struct MoveData;		//
	MoveData* moveData;		// 移動に使うデータ

public:
	MoveDrawObject(DrawObject* drawObject);
	~MoveDrawObject();

	const DrawObject* getDrawObject() const{
		return drawObject;
	}

	void update();
	void setVector(const Vector3d& vec);
	void setVector(double x, double y, double z);
	void setAccelVector(const Vector3d& accel_vec);
	void setAccelVector(double x, double y, double z);
	void setAngleVector(double vec_r);
	void setAccelAngleVector(double accel_vec_r);
};

#endif