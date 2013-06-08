#ifndef ___Class_DrawObject
#define ___Class_DrawObject

#include "MyPoint.h"

struct MaterialData;

class DrawObject{
	// --- DrawObjectの座標や回転を決めるメンバ --- //
	Point3d pt;						// 描画の基準点
	double  angle;					// 回転する角度
	double  rotate_vec[3];			// 回転方向を定めるベクトル

	// --- materialの色を決めるメンバ --- //
	float   ambient[4];				// 環境光
	float   diffuse[4];				// 拡散光
	float   specular[4];			// 鏡面光
	float   shininess;				// 鏡面指数

	static void setArray(float arr[], float a, float b, float c, float d){
		arr[0] = a;		arr[1] = b;
		arr[2] = c;		arr[3] = d;
	}

protected:
	void setPosition() const;		// 相対的に自分の座標へ移動する
	void setMaterial() const;		// 材質を設定する
	virtual void draw() const = 0;

public:
	DrawObject(GLdouble x = 0.0, GLdouble y = 0.0, GLdouble z = 0.0);

	DrawObject(const Point3d& pt);
	// 仮想デストラクタ
	virtual ~DrawObject();

	void draw(bool useShelter, bool useMaterial) const;

	// --- 座標の移動や取得 --- //
	const Point3d& getPoint(){
		return pt;
	}
	void move(const Point3d& pt){
		this->pt = pt;
	}
	void move(const Vector3d& vec){
		pt.move(vec);
	}


	// --- materialの色の設定 --- //
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


	// --- DrawObjectの回転方向の指定や回転量の指定や取得 --- //
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