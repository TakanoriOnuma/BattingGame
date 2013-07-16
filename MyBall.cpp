#include "MyBall.h"
#include "BallVariety.h"
#include "BallStraight.h"

#include "OpenGL.h"
#include "read_bitmap.h"

MyBall::MyBall(double radius, int sides)
	: MySphere(radius, sides), state(State::HANDED), message(NULL), gravity(0.005)
{
	init();
}

MyBall::MyBall(double x, double y, double z, double radius, int sides)
	: MySphere(x, y, z, radius, sides), state(State::HANDED), message(NULL), gravity(0.005)
{
	init();
}

MyBall::~MyBall()
{
	glDeleteTextures(1, &texNumber);
}

void MyBall::init()
{
	variety = new Straight(0.0);		// とりあえず入れておく

	glGenTextures(1, &texNumber);		// 空いているtexNumberを見つける

	// --- texNumberとバインドする --- //
	glBindTexture(GL_TEXTURE_2D, texNumber);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	// --- テクスチャの初期設定 --- //
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	// --- BMPファイルの読み込み --- //
	int width, height;
	unsigned char* pixels;
	// ファイルを読み込めなかったら
	if(ReadBitMapData("texture/ball.bmp", &width, &height, &pixels) == 0){
		return;			// 何もせず終了する
	}

	// --- 画像データをテクスチャに読み込む --- //
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height,
		0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

	free(pixels);		// 画像データをサーバ側に渡したためもう必要はない

	GLUquadric* quad = this->quadObject.getQuadric();
	gluQuadricTexture(quad, GL_TRUE);
}

void MyBall::draw() const
{
	glBindTexture(GL_TEXTURE_2D, texNumber);
	glEnable(GL_TEXTURE_2D);

	MySphere::draw();

	glDisable(GL_TEXTURE_2D);
}

void MyBall::update()
{
	// 誰かに持たれている状態でなければ
	if(state != State::HANDED){
		move(vec);			// 自分の座標を移動する

		// ボールを投げている
		if(vec.z > 0.0){
			vec.y -= gravity;
			variety->change(*this);		// ボールによって動きが変わる
		}
		// 打たれたあと
		else{
			vec.y -= 0.01;
		}
	}
}

void MyBall::emit(Variety* variety)
{
	state = State::ISOLATED;
	delete this->variety;		// 前の球種は削除して
	this->variety = variety;	// 球種をセット
	if(message != NULL){
		message->message();		// メッセージを送る
	}

}