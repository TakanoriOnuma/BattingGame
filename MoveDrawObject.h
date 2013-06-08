#ifndef ___Class_MoveDrawObject
#define ___Class_MoveDrawObject


class DrawObject;
struct Vector3d;
// DrawObject���ȒP�ɓ�������悤�ɂ����N���X
// DrawObject�̔j���͎����ōs��
class MoveDrawObject{
	DrawObject* drawObject;

	struct MoveData;		//
	MoveData* moveData;		// �ړ��Ɏg���f�[�^

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