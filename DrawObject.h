#ifndef ___Class_DrawObject
#define ___Class_DrawObject

#include "MyPoint.h"
#include "RectangularParallelepiped.h"

struct MaterialData;

class DrawObject{
	// --- DrawObject‚ÌÀ•W‚â‰ñ“]‚ðŒˆ‚ß‚éƒƒ“ƒo --- //
	Point3d pt;						// •`‰æ‚ÌŠî€“_
	double  angle;					// ‰ñ“]‚·‚éŠp“x
	double  rotate_vec[3];			// ‰ñ“]•ûŒü‚ð’è‚ß‚éƒxƒNƒgƒ‹

	// --- material‚ÌF‚ðŒˆ‚ß‚éƒƒ“ƒo --- //
	float   ambient[4];				// ŠÂ‹«Œõ
	float   diffuse[4];				// ŠgŽUŒõ
	float   specular[4];			// ‹¾–ÊŒõ
	float   shininess;				// ‹¾–ÊŽw”


	static void setArray(float arr[], float a, float b, float c, float d){
		arr[0] = a;		arr[1] = b;
		arr[2] = c;		arr[3] = d;
	}

protected:
	// --- DrawObject‚Ì‘åŽG”c‚È‘å‚«‚³‚ð’m‚éƒƒ“ƒo --- //
	RectangularParallelepiped rectParallel;		// ’¼•û‘Ì

	void setPosition() const;		// ‘Š‘Î“I‚ÉŽ©•ª‚ÌÀ•W‚ÖˆÚ“®‚·‚é
	void setMaterial() const;		// ÞŽ¿‚ðÝ’è‚·‚é
	virtual void draw() const = 0;

public:
	DrawObject(GLdouble x = 0.0, GLdouble y = 0.0, GLdouble z = 0.0);

	DrawObject(const Point3d& pt);
	// ‰¼‘zƒfƒXƒgƒ‰ƒNƒ^
	virtual ~DrawObject();

	void draw(bool useShelter, bool useMaterial) const;

	// --- À•W‚ÌˆÚ“®‚âŽæ“¾ --- //
	const Point3d& getPoint(){
		return pt;
	}
	void move(const Point3d& pt){
		this->pt = pt;
	}
	void move(const Vector3d& vec){
		pt.move(vec);
	}

	// --- ‘åŽG”c‚È‘å‚«‚³‚ðŽæ“¾ --- //
	const RectangularParallelepiped& getRectangularParallelepiped() const{
		return rectParallel;
	}

	// --- material‚ÌF‚ÌÝ’è --- //
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


	// --- DrawObject‚Ì‰ñ“]•ûŒü‚ÌŽw’è‚â‰ñ“]—Ê‚ÌŽw’è‚âŽæ“¾ --- //
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