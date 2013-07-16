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
	variety = new Straight(0.0);		// �Ƃ肠��������Ă���

	glGenTextures(1, &texNumber);		// �󂢂Ă���texNumber��������

	// --- texNumber�ƃo�C���h���� --- //
	glBindTexture(GL_TEXTURE_2D, texNumber);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	// --- �e�N�X�`���̏����ݒ� --- //
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	// --- BMP�t�@�C���̓ǂݍ��� --- //
	int width, height;
	unsigned char* pixels;
	// �t�@�C����ǂݍ��߂Ȃ�������
	if(ReadBitMapData("texture/ball.bmp", &width, &height, &pixels) == 0){
		return;			// ���������I������
	}

	// --- �摜�f�[�^���e�N�X�`���ɓǂݍ��� --- //
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height,
		0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

	free(pixels);		// �摜�f�[�^���T�[�o���ɓn�������߂����K�v�͂Ȃ�

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
	// �N���Ɏ�����Ă����ԂłȂ����
	if(state != State::HANDED){
		move(vec);			// �����̍��W���ړ�����

		// �{�[���𓊂��Ă���
		if(vec.z > 0.0){
			vec.y -= gravity;
			variety->change(*this);		// �{�[���ɂ���ē������ς��
		}
		// �ł��ꂽ����
		else{
			vec.y -= 0.01;
		}
	}
}

void MyBall::emit(Variety* variety)
{
	state = State::ISOLATED;
	delete this->variety;		// �O�̋���͍폜����
	this->variety = variety;	// ������Z�b�g
	if(message != NULL){
		message->message();		// ���b�Z�[�W�𑗂�
	}

}