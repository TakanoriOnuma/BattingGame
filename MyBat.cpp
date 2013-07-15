#include "OpenGL.h"
#include "read_bitmap.h"

#include "MyBat.h"

#include <stdio.h>

MyBat::MyBat(double x, double y, double z)
	: DrawableObject(x, y, z)
{
	init();
}

MyBat::MyBat(const Point3d& pt)
	: DrawableObject(pt)
{
	init();
}

void MyBat::init()
{
	rectBox.setRectBox(0.4, 0.4, 2.3);

	glGenTextures(1, &texNumber);		// 空いているtexNumberを見つける

	printf("MyBat:%d\n", texNumber);

	// --- BMPファイルの読み込み --- //
	int width, height;
	unsigned char* pixels;
	// ファイルを読み込めなかったら
	if(ReadBitMapData("texture/griptape.bmp", &width, &height, &pixels) == 0){
		return;		// 何もせず終了する
	}

	// --- texNumberとバインドする --- //
	glBindTexture(GL_TEXTURE_2D, texNumber);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	// --- テクスチャの初期設定 --- //
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);


	// --- 画像データをテクスチャに読み込む --- //
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height,
		0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

	free(pixels);		// 画像データをサーバ側に渡したためもう必要はない

	GLUquadric* quad = this->quadObject.getQuadric();
	gluQuadricTexture(quad, GL_TRUE);
}

void MyBat::draw() const
{
	GLUquadric* quad = quadObject.getQuadric();

	gluQuadricOrientation(quad, GLU_OUTSIDE);
	gluDisk(quad, 0.0, 0.18, 16, 16);

	glTranslated(0.0, 0.0, -0.1);
	gluCylinder(quad, 0.2, 0.18, 0.1, 16, 1);

	glTranslated(0.0, 0.0, -0.6);
	gluCylinder(quad, 0.2, 0.2, 0.6, 16, 1);

	glTranslated(0.0, 0.0, -0.9);
	gluCylinder(quad, 0.1, 0.2, 0.9, 16, 1);

	glEnable(GL_TEXTURE_2D);
	glTranslated(0.0, 0.0, -0.6);
	gluCylinder(quad, 0.1, 0.1, 0.6, 16, 1);
	glDisable(GL_TEXTURE_2D);

	gluDisk(quad, 0.1, 0.15, 16, 16);

	glTranslated(0.0, 0.0, -0.1);
	gluCylinder(quad, 0.15, 0.15, 0.1, 16, 1);

	gluQuadricOrientation(quad, GLU_INSIDE);
	gluDisk(quad, 0.0, 0.15, 16, 1);

	glTranslated(-0.2, -0.2, 0.0);
}