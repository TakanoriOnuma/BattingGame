#ifndef ___Class_DrawObject
#define ___Class_DrawObject

#include "MyPoint.h"
#include "RectangularParallelepiped.h"

struct MaterialData;

class DrawObject{
	// --- DrawObject�̍��W���]�����߂郁���o --- //
	Point3d pt;						// �`��̊�_
	double  angle;					// ��]����p�x
	double  rotate_vec[3];			// ��]�������߂�x�N�g��

	// --- material�̐F�����߂郁���o --- //
	float   ambient[4];				// ����
	float   diffuse[4];				// �g�U��
	float   specular[4];			// ���ʌ�
	float   shininess;				// ���ʎw��


	static void setArray(float arr[], float a, float b, float c, float d){
		arr[0] = a;		arr[1] = b;
		arr[2] = c;		arr[3] = d;
	}

protected:
	// --- DrawObject�̑�G�c�ȑ傫����m�郁���o --- //
	RectangularParallelepiped rectParallel;		// ������

	void setPosition() const;		// ���ΓI�Ɏ����̍��W�ֈړ�����
	void setMaterial() const;		// �ގ���ݒ肷��
	virtual void draw() const = 0;

public:
	DrawObject(GLdouble x = 0.0, GLdouble y = 0.0, GLdouble z = 0.0);

	DrawObject(const Point3d& pt);
	// ���z�f�X�g���N�^
	virtual ~DrawObject();

	void draw(bool useShelter, bool useMaterial) const;

	// --- ���W�̈ړ���擾 --- //
	const Point3d& getPoint(){
		return pt;
	}
	void move(const Point3d& pt){
		this->pt = pt;
	}
	void move(const Vector3d& vec){
		pt.move(vec);
	}

	// --- ��G�c�ȑ傫�����擾 --- //
	const RectangularParallelepiped& getRectangularParallelepiped() const{
		return rectParallel;
	}

	// --- material�̐F�̐ݒ� --- //
	virtual void init_material_color();
	virtual void setAmbient(float red, float green, float blue, float alpha = 1.0f){
		setArray(ambient, red, green, blue, alpha);
	}
	virtual void setDiffuse(float red, float green, float blue, float alpha = 1.0f){
		setArray(diffuse, red, green, blue, alpha);
	}
	virtual void setSpecular(float red, float green, float blue, float alpha = 1.0f){
		setArray(specular, red, green, blue, alpha);
	}
	virtual void setShininess(float shininess){
		this->shininess = shininess;
	}
	virtual void setMaterialData(const MaterialData& matData);


	// --- DrawObject�̉�]�����̎w����]�ʂ̎w���擾 --- //
	void setRotateVector(double x, double y, double z){
		rotate_vec[0] = x;
		rotate_vec[1] = y;
		rotate_vec[2] = z;
	}
	void setAngle(double angle){
		this->angle = angle;
	}
	void addAngle(double value){
		angle += value;
	}
	double getAngle() const{
		return angle;
	}

};


#endif