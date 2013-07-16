#include "Game.h"
#include "MyBox.h"
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
	MyBox  backWall;		// ���̕�
	MyBall ball;
	Ground ground;
	BattingRobot battingRobot;
	PitchingRobotArm pitchingRobotArm;

	Rectangle2D batting_field;
	MyCircle circle;

	DrawableObjects()
		: backWall(0.0, 0.0, 0.0, 1.0, 20.0, 2.0),
		ball(0.2),
		ground(0.0, -1.8, -20.0, 20, 60),
		battingRobot(-2.3, 0.9, 3.0),
		pitchingRobotArm(0.0, -1.5, -20.0),
		batting_field(0.0, -0.1, 3.0, 1.5, 1.5, ColorData(1.0, 0.0, 0.0)),
		circle(0.0, 0.0, 3.0, 0.1, ColorData(0.0, 1.0, 0.0))
	{
		Point3d move_pt;
		move_pt.x = ground.getPoint().x;
		move_pt.y = ground.getPoint().y + backWall.getRectBox().height;
		move_pt.z = ground.getPoint().z - ground.getRectBox().length / 2;
		backWall.move(move_pt);
		backWall.setMaterialData(MaterialData::createMaterialData(Color::BLUE));
		
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
		backWall.draw(true, true);
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
	result_str = "";			// �󕶎�
	difficulity_str = "easy";
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
		// �܂��{�[�����]���Ă���Ȃ�
		if(ball_num > 0 && objects->pitchingRobotArm.getArmAngle() == 0.0){
			objects->pitchingRobotArm.ball_throw();				// �{�[���𓊂���
		}
	}
	if(keyboardManager.isPushCharKey('y') && !check_flag){
		check_flag = true;		// �ȍ~�`�F�b�N������
		result_str = "";		// �󕶎��ɂ���
		objects->pitchingRobotArm.hand_ball(&objects->ball);	// �{�[������������
		objects->pitchingRobotArm.setArmAngle(0.0);				// ������Ԃɖ߂�
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
		if(camera->getDistance() > 80.0){
			camera->setDistance(80.0);
		}
	}

	// --- HitProcesser�̐ݒ� --- //
	if(keyboardManager.isPushCharKey('z')){
		hitProcesser = RoughHitProcesser::getInstance();
	}
	else if(keyboardManager.isPushCharKey('x')){
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

	// --- �t�B�[���h�̕��̐ݒ� --- //
	if(keyboardManager.isPushCharKey('8')){
		objects->batting_field.setWidth(1.0);
		objects->batting_field.setHeight(1.0);
	}
	else if(keyboardManager.isPushCharKey('9')){
		objects->batting_field.setWidth(1.5);
		objects->batting_field.setHeight(1.5);
	}

	// --- ������{�[���̃��x���̎w�� --- //
	if(keyboardManager.isPushCharKey('1')){
		objects->pitchingRobotArm.setDifficulity(PitchingRobotArm::Difficulity::EASY);
		difficulity_str = "easy";
	}
	else if(keyboardManager.isPushCharKey('2')){
		objects->pitchingRobotArm.setDifficulity(PitchingRobotArm::Difficulity::NORMAL);
		difficulity_str = "normal";
	}

	// --- �{�[���̐��̃��Z�b�g --- //
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

	// �{�[�����O�֏o����
	const Rectangle2D& batting_field = objects->batting_field;
	double margin_width = (batting_field.getPoint().z - ball.getPoint().z) / 3;
	if(ball.getPoint().x < batting_field.getPoint().x - batting_field.getWidth() - margin_width ||
		ball.getPoint().x > batting_field.getPoint().x + batting_field.getWidth() + margin_width){
			result_str = "foul";	// �t�@�E��
			score += 1;				// �X�R�A��1���Z
			check_flag = false;		// �������ׂȂ�
			return;
	}

	// �{�[�����O���E���h�̒n�ʂɓ���������
	if(ball.getPoint().y - ball.getRectBox().height < objects->ground.getPoint().y){
		result_str = "hit";			// �q�b�g
		score += 2;					// �X�R�A��2���Z
		check_flag = false;			// �������ׂȂ�
		return;
	}

	// �ǂ��z������
	const MyBox& backWall = objects->backWall;
	if(ball.getPoint().z + ball.getRectBox().length <
		backWall.getPoint().z - backWall.getRectBox().length / 2){
			// ���ʂ��Ă�����
			if(ball.getPoint().y - ball.getRectBox().height > backWall.getPoint().y){
				result_str = "homerun";		// �z�[������
				score += 3;					// �X�R�A��3���Z
			}
			// ���ʂ�Ȃ�������
			else{
				result_str = "hit";			// �q�b�g
				score += 2;					// �X�R�A��2���Z
			}
			check_flag = false;			// �������ׂȂ�
			return;
	}
}

void Game::hit_process()
{
	MyBall& ball = objects->ball;
	// �{�[�����O���E���h�̒n�ʂɓ���������
	if(ball.getPoint().y - ball.getRectBox().height < objects->ground.getPoint().y){
		const Point3d& pt = ball.getPoint();
		ball.move(Point3d(pt.x, objects->ground.getPoint().y + ball.getRectBox().height, pt.z));
		const Vector3d& vec = ball.getVector();
		ball.setVector(vec.x, -0.8 * vec.y, vec.z);		// ��������������
	}
}

IScene* Game::update()
{
	objects->update();

	// �{�[�����Ɨ����Ă�����
	if(objects->ball.getState() == MyBall::State::ISOLATED){
		// check_flag�������Ă�����
		if(check_flag){
			check_ball();		// �{�[���𒲂ׂ�
		}
		hit_process();			// �{�[�����n�ʂɓ�����Ƃ��̏���
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