#include "Game.h"
#include "Ground.h"
#include "BattingRobot.h"
#include "PitchingRobotArm.h"
#include "MaterialData.h"
#include "KeyboardManager.h"
#include "MouseManager.h"
#include "MouseListener.h"
#include "Camera.h"
#include "MyBall.h"
#include "Rectangle2D.h"
#include "MyCircle.h"
#include "RoughHitProcesser.h"
#include "NoDelayHitProcesser.h"
#include "EmitionMesseage.h"
#include "MouseDevice.h"
#include "KeyboardDevice.h"

#include <iostream>
#include <string>
#include <sstream>

using namespace std;

static void outPoint(string str, const Point3d& pt)
{
	cout << str << "(" << pt.x << ", " << pt.y << ", " << pt.z << ")" << endl;
}
static void outVector(string str, const Vector3d& vec)
{
	cout << str << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")" << endl;
}


static void drawString(const char* str)
{
	while(*str != '\0'){
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *str);
		++str;
	}
}

// ===== Game�N���X��DrawableObject�Q ===== //
struct Game::DrawableObjects{
	MyBall ball;
	Ground ground;
	BattingRobot battingRobot;
	PitchingRobotArm pitchingRobotArm;

	Rectangle2D batting_field;
	MyCircle circle;

	DrawableObjects()
		: ball(0.2),
		ground(0.0, -1.8, -10.0, 20, 40),
		battingRobot(-2.3, 0.9, 3.0),
		pitchingRobotArm(0.0, -1.5, -20.0),
		batting_field(0.0, -0.1, 3.0, 1.5, 1.5, ColorData(1.0, 0.0, 0.0)),
		circle(0.0, 0.0, 3.0, 0.1, ColorData(0.0, 1.0, 0.0))
	{
		ball.setMaterialData(MaterialData::createMaterialData(Jewel::OBSIDIAN));
		battingRobot.setRotateVector(0.0, 1.0, 0.0);
		battingRobot.setAngle(90.0);
		battingRobot.setMaterialData(MaterialData::createMaterialData(Jewel::TURQUOISE));
		battingRobot.setStandardPoint(batting_field.getPoint());
		pitchingRobotArm.setMaterialData(MaterialData::createMaterialData(Ore::BRONZE));
		pitchingRobotArm.hand_ball(&ball);
		pitchingRobotArm.setTargetField(&batting_field);
	}

	void draw() const{
		if(ball.getState() != MyBall::State::HANDED){
			ball.draw(true, true);
		}
		ground.draw(true, true);
		battingRobot.draw(true, true);
		pitchingRobotArm.draw(true, true);

		batting_field.draw(true, true);
		circle.draw(true, true);
	}

	// �K�v�̂�����̂���update����
	void update(){
		ball.update();
		battingRobot.update();
		pitchingRobotArm.update();
	}
};


// ===== �{�[���������ꂽ�Ƃ��̃��X�i�[ ===== //
class Game::EmitionListener : public EmitionMessage
{
	Game& parent;

public:
	EmitionListener(Game& parent) : parent(parent)
	{
	}

	void message() override{
		parent.ball_num--;		// �{�[���̐������炷
	}
};



// ====== �Q�[���N���X�̒�` ===== //
Game::Game()
	: MAX_BALL_NUM(10)
{
	score = 0;
	check_flag = true;
	ball_num = MAX_BALL_NUM;
	result_str = "";		// �󕶎�
	objects = new DrawableObjects();
	camera  = new Camera();
	usingDevice = new MouseDevice(objects->battingRobot, objects->circle, objects->batting_field, *camera);
	usingDeviceName = "MouseDevice";
//	usingDevice = new KeyboardDevice(objects->battingRobot, objects->circle, objects->batting_field);
	hitProcesser = NoDelayHitProcesser::getInstance();

	emitionListener = new EmitionListener(*this);
	objects->ball.setEmitionMessage(emitionListener);
}

Game::~Game()
{
	delete objects;
	delete camera;
	delete usingDevice;

	// �{���Ȃ�I�u�U�[�o�[���������Ȃ��Ƃ����Ȃ����A
	// �{�[�����g���j������邽�߉������Ȃ��Ă����͂Ȃ�
	delete emitionListener;
}

void Game::check_char_key()
{
	KeyboardManager& keyboardManager = KeyboardManager::getInstance();
	if(keyboardManager.isPushCharKey('t')){
		objects->battingRobot.swing(objects->circle.getPoint());
	}
	if(keyboardManager.isPushCharKey('o')){
		// �܂��{�[�����]���Ă���Ȃ�
		if(ball_num > 0){
			objects->pitchingRobotArm.ball_throw();				// �{�[���𓊂���
		}
	}
	if(keyboardManager.isPushCharKey('h')){
		check_flag = true;		// �ȍ~�`�F�b�N������
		result_str = "";		// �󕶎��ɂ���
		objects->pitchingRobotArm.hand_ball(&objects->ball);	// �{�[������������
	}
	if(keyboardManager.isPushCharKey('k')){
		objects->pitchingRobotArm.setTargetField(&objects->batting_field);
	}
	else if(keyboardManager.isPushCharKey('l')){
		objects->pitchingRobotArm.setTargetField(NULL);
	}

	// --- �J�����̒��� --- //
	if(keyboardManager.isPushCharKey('a')){
		camera->addAngle_xz(5.0);
	}
	else if(keyboardManager.isPushCharKey('d')){
		camera->addAngle_xz(-5.0);
	}
	if(keyboardManager.isPushCharKey('w')){
		camera->addAngle_yz(1.0);
	}
	else if(keyboardManager.isPushCharKey('s')){
		camera->addAngle_yz(-1.0);
		if(camera->getAngle_yz() < 0.0){
			camera->setAngle_yz(0.0);
		}
	}
	if(keyboardManager.isPushCharKey('n')){
		camera->addDistance(-1.0);
	}
	if(keyboardManager.isPushCharKey('f')){
		camera->addDistance(1.0);
		if(camera->getDistance() > 50.0){
			camera->setDistance(50.0);
		}
	}

	// --- ������t�B�[���h�̎w�� --- //
	if(keyboardManager.isPushCharKey('z')){
		objects->pitchingRobotArm.setTargetField(NULL);
	}
	else if(keyboardManager.isPushCharKey('x')){
		objects->pitchingRobotArm.setTargetField(&objects->batting_field);
	}

	// --- HitProcesser�̐ݒ� --- //
	if(keyboardManager.isPushCharKey('c')){
		hitProcesser = RoughHitProcesser::getInstance();
	}
	else if(keyboardManager.isPushCharKey('v')){
		hitProcesser = NoDelayHitProcesser::getInstance();
	}

	// --- usingDevice�̐ݒ� --- //
	if(keyboardManager.isPushCharKey('m')){
		delete usingDevice;
		usingDevice = new MouseDevice(objects->battingRobot, objects->circle, objects->batting_field, *camera);
		usingDeviceName = "MouseDevice";
	}
	else if(keyboardManager.isPushCharKey('k')){
		delete usingDevice;
		usingDevice = new KeyboardDevice(objects->battingRobot, objects->circle, objects->batting_field);
		usingDeviceName = "KeyboardDevice";
	}

	// --- ��Փx�̐ݒ� --- //
	if(keyboardManager.isPushCharKey('1')){
		objects->batting_field.setWidth(1.0);
		objects->batting_field.setHeight(1.0);
	}
	else if(keyboardManager.isPushCharKey('2')){
		objects->batting_field.setWidth(1.5);
		objects->batting_field.setHeight(1.5);
	}

	if(keyboardManager.isPushCharKey('r')){
		score = 0;
		ball_num = MAX_BALL_NUM;
		result_str = "";		// �󕶎��ɂ���
	}
}

void Game::check_special_key()
{
	KeyboardManager& keyboardManager = KeyboardManager::getInstance();

	if(keyboardManager.isPushSpecialKey(SpecialKey::LEFT)){
		objects->battingRobot.addAngle(-5.0);
	}
	else if(keyboardManager.isPushSpecialKey(SpecialKey::RIGHT)){
		objects->battingRobot.addAngle(5.0);
	}

	if(keyboardManager.isPushSpecialKey(SpecialKey::UP)){
		if(keyboardManager.isPushCharKey('r')){
			objects->battingRobot.run();
		}
		else{
			objects->battingRobot.walk();
		}
	}
}

// �{�[���̂���ꏊ�ɂ���Ēǉ�����X�R�A��ς���
void Game::check_ball()
{
	MyBall& ball = objects->ball;
	const Ground& ground = objects->ground;
	// �o�b�e�B���O����̈���{�[��2�������ɂ�������
	if(ball.getPoint().z - 2 * ball.getRectBox().length > objects->batting_field.getPoint().z){
		result_str = "strike";			// �X�g���C�N
		cout << "no check" << endl;
		check_flag = false;			// �������ׂȂ�
		return;
	}

	// �{�[�����O���E���h�̘e�̊O�֏o����
	if(ball.getPoint().x < ground.getPoint().x - ground.getRectBox().width / 2 ||
		ball.getPoint().x > ground.getPoint().x + ground.getRectBox().width / 2){
			result_str = "foul";	// �t�@�E��
			score += 1;				// �X�R�A��1���Z
			check_flag = false;		// �������ׂȂ�
			return;
	}

	// �{�[�����O���E���h�̒n�ʂɓ���������
	if(ball.getPoint().y - ball.getRectBox().height < objects->ground.getPoint().y){
		result_str = "hit";			// �q�b�g
		cout << "reflect" << endl;
		const Point3d& pt = ball.getPoint();
		ball.move(Point3d(pt.x, objects->ground.getPoint().y + ball.getRectBox().height, pt.z));
		outPoint("ball.point", pt);
		const Vector3d& vec = ball.getVector();
		ball.setVector(vec.x, -vec.y, vec.z);
		outVector("ball.vec", vec);
		score += 2;					// �X�R�A��2���Z
		check_flag = false;			// �������ׂȂ�
		return;
	}

	// �{�[�����O���E���h�̉��܂Ŕ�񂾂�
	if(ball.getPoint().z + ball.getRectBox().length < ground.getPoint().z - ground.getRectBox().length){
		result_str = "homerun";		// �z�[������
		score += 3;					// �X�R�A��3���Z
		check_flag = false;			// �������ׂȂ�
		return;
	}
}

IScene* Game::update()
{
	objects->update();

	// �{�[�����Ɨ����Ă��āAcheck_flag�������Ă�����
	if(objects->ball.getState() == MyBall::State::ISOLATED && check_flag){
		check_ball();		// �{�[���𒲂ׂ�
	}

	check_char_key();
//	check_special_key();

	usingDevice->movePoint();
	usingDevice->swing();

	hitProcesser->hitProcess(objects->ball, objects->battingRobot);

	return this;
}


void Game::display() const
{
	static GLfloat lightpos0[] = { 0.0, 5.0, 5.0, 1.0 };
	static GLfloat lightpos1[] = { 0.0, 5.0, -10.0, 1.0 };
	/* ��ʃN���A */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/* ���f���E�r���[�ϊ��s��̏����� */
	glLoadIdentity();

	/* �J�����̃Z�b�g */
	camera->setCamera();

	/* �����̈ʒu���w�� */
	glLightfv(GL_LIGHT0, GL_POSITION, lightpos0);
	glLightfv(GL_LIGHT1, GL_POSITION, lightpos1);

	objects->draw();

	glDisable(GL_LIGHTING);
	if(objects->pitchingRobotArm.isSetTargetField()){
		glColor3d(1.0, 0.0, 0.0);
		glRasterPos3d(-3.0, 2.0, 0.0);
		drawString("Throw ball in red box");
	}
	else{
		glColor3d(0.0, 1.0, 0.0);
		glRasterPos3d(-3.0, 2.0, 0.0);
		drawString("Throw ball at green circle");
	}
	if(hitProcesser == RoughHitProcesser::getInstance()){
		glColor3d(0.0, 1.0, 1.0);
		glRasterPos3d(-3.0, 1.5, 0.0);
		drawString("RoughHitProcesser");
	}
	else if(hitProcesser == NoDelayHitProcesser::getInstance()){
		glColor3d(1.0, 0.0, 1.0);
		glRasterPos3d(-3.0, 1.5, 0.0);
		drawString("NoDelayHitProcesser");
	}

	glColor3d(0.5, 0.0, 0.5);
	glRasterPos3d(-3.0, 1.0, 0.0);
	drawString(usingDeviceName.c_str());

	// �{�[���̎c��̐���\��
	stringstream stream;
	stream << ball_num;
	glColor3d(0.0, 0.0, 1.0);
	glRasterPos3d(1.5, 2.0, 0.0);
	drawString("Ball:");
	drawString(stream.str().c_str());

	// �X�R�A�̕\��
	stream.str("");		// �o�b�t�@�̃N���A
	stream << score;
	glColor3d(0.0, 0.0, 1.0);
	glRasterPos3d(1.5, 1.5, 0.0);
	drawString("Score:");
	drawString(stream.str().c_str());

	// ���ʂ̕\��
	glColor3d(1.0, 0.0, 1.0);
	glRasterPos3d(1.7, 0.5, 0.0);
	drawString(result_str.c_str());

	glEnable(GL_LIGHTING);

//	glutSwapBuffers();			// GameDecorator���ŏo�͂�����
}

// �Q�[�����~�߂�(���̋@�\������Ȃ�GameDecorator���Ŏ~�߂�K�v�͂Ȃ���������Ȃ�)
void Game::stop()
{
	usingDevice->resetEventHandlar();
}

// �Q�[�����ĊJ����
void Game::restart()
{
	usingDevice->setEventHandlar();
}