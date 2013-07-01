#include "OpenGL.h"

#include "DrawableObject.h"
#include "MaterialData.h"


DrawableObject::DrawableObject(GLdouble x, GLdouble y, GLdouble z)
	: pt(x, y, z), angle(0.0)
{
	init_material_color();
	setRotateVector(0.0, 0.0, 0.0);
}

DrawableObject::DrawableObject(const Point3d& pt)
	: pt(pt), angle(0.0)
{
	init_material_color();
	setRotateVector(0.0, 0.0, 0.0);
}

DrawableObject::~DrawableObject()
{

}

void DrawableObject::setPosition() const{
	glTranslated(pt.x, pt.y, pt.z);
	glRotated(angle, rotate_vec[0], rotate_vec[1], rotate_vec[2]);
}

void DrawableObject::setMaterial() const{
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialf(GL_FRONT, GL_SHININESS, shininess);
}


/*	
 *	変換行列を退避するならuseShelterをtrueに、
 *	材質の設定をしたいならuseMaterialをtrueにする
 */
void DrawableObject::draw(bool useShelter, bool useMaterial) const
{
	if(useShelter)
		glPushMatrix();
	if(useMaterial)
		setMaterial();

	setPosition();
	draw();					// サブクラスの描画
	
	if(useShelter)
		glPopMatrix();
}

void DrawableObject::setMaterialData(const MaterialData& matData)
{
	for(int i = 0; i < 4; i++){
		ambient[i] = matData.ambient[i];
		diffuse[i] = matData.diffuse[i];
		specular[i] = matData.specular[i];
	}
	shininess = matData.shininess;
}

void DrawableObject::init_material_color(){
	setAmbient(0.2f, 0.2f, 0.2f);
	setDiffuse(0.8f, 0.8f, 0.8f);
	setSpecular(0.0f, 0.0f, 0.0f);
	setShininess(0.0f);
}