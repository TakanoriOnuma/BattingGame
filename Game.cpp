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

// ===== GameクラスのDrawableObject群 ===== //
struct Game::DrawableObjects{
	MyBox  backWall;		// 後ろの壁
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

	// 必要のあるものだけupdateする
	void update(){
		ball.update();
		battingRobot.update();
		pitchingRobotArm.update();
	}
};


// ===== ボールが放たれたときのリスナー ===== //
class Game::EmitionListener : public EmitionMessage
{
	Game& parent;

public:
	EmitionListener(Game& parent) : parent(parent)
	{
	}

	void message() override{
		parent.ball_num--;		// ボールの数を減らす
	}
};



// ====== ゲームクラスの定義 ===== //
Game::Game()
	: MAX_BALL_NUM(10)
{
	score = 0;
	check_flag = true;
	ball_num = MAX_BALL_NUM;
	result_str = "";		// 空文字
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

	// 本来ならオブザーバーを解除しないといけないが、
	// ボール自身も破棄されるため解除しなくても問題はない
	delete emitionListener;
}

void Game::check_char_key()
{
	KeyboardManager& keyboardManager = KeyboardManager::getInstance();
	if(keyboardManager.isPushCharKey('t')){
		objects->battingRobot.swing(objects->circle.getPoint());
	}
	if(keyboardManager.isPushCharKey('o')){
		// まだボールが余っているなら
		if(ball_num > 0){
			objects->pitchingRobotArm.ball_throw();				// ボールを投げる
		}
	}
	if(keyboardManager.isPushCharKey('h')){
		check_flag = true;		// 以降チェックさせる
		result_str = "";		// 空文字にする
		objects->pitchingRobotArm.hand_ball(&objects->ball);	// ボールを持たせる
	}
	if(keyboardManager.isPushCharKey('k')){
		objects->pitchingRobotArm.setTargetField(&objects->batting_field);
	}
	else if(keyboardManager.isPushCharKey('l')){
		objects->pitchingRobotArm.setTargetField(NULL);
	}

	// --- カメラの調整 --- //
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

	// --- 投げるフィールドの指定 --- //
	if(keyboardManager.isPushCharKey('z')){
		objects->pitchingRobotArm.setTargetField(NULL);
	}
	else if(keyboardManager.isPushCharKey('x')){
		objects->pitchingRobotArm.setTargetField(&objects->batting_field);
	}

	// --- HitProcesserの設定 --- //
	if(keyboardManager.isPushCharKey('c')){
		hitProcesser = RoughHitProcesser::getInstance();
	}
	else if(keyboardManager.isPushCharKey('v')){
		hitProcesser = NoDelayHitProcesser::getInstance();
	}

	// --- usingDeviceの設定 --- //
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

	// --- フィールドの幅の設定 --- //
	if(keyboardManager.isPushCharKey('8')){
		objects->batting_field.setWidth(1.0);
		objects->batting_field.setHeight(1.0);
	}
	else if(keyboardManager.isPushCharKey('9')){
		objects->batting_field.setWidth(1.5);
		objects->batting_field.setHeight(1.5);
	}

	// --- 投げるボールのレベルの指定 --- //
	if(keyboardManager.isPushCharKey('1')){
		objects->pitchingRobotArm.setDifficulity(PitchingRobotArm::Difficulity::EASY);
	}
	else if(keyboardManager.isPushCharKey('2')){
		objects->pitchingRobotArm.setDifficulity(PitchingRobotArm::Difficulity::NORMAL);
	}

	// --- ボールの数のリセット --- //
	if(keyboardManager.isPushCharKey('r')){
		score = 0;
		ball_num = MAX_BALL_NUM;
		result_str = "";		// 空文字にする
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

// ボールのいる場所によって追加するスコアを変える
void Game::check_ball()
{
	MyBall& ball = objects->ball;
	const Ground& ground = objects->ground;
	// バッティングする領域よりボール2つ分も後ろにあったら
	if(ball.getPoint().z - 2 * ball.getRectBox().length > objects->batting_field.getPoint().z){
		result_str = "strike";			// ストライク
		cout << "no check" << endl;
		check_flag = false;			// もう調べない
		return;
	}

	// ボールが外へ出たら
	const Rectangle2D& batting_field = objects->batting_field;
	double margin_width = (batting_field.getPoint().z - ball.getPoint().z) / 3;
	if(ball.getPoint().x < batting_field.getPoint().x - batting_field.getWidth() - margin_width ||
		ball.getPoint().x > batting_field.getPoint().x + batting_field.getWidth() + margin_width){
			result_str = "foul";	// ファウル
			score += 1;				// スコアを1加算
			check_flag = false;		// もう調べない
			return;
	}

	// ボールがグラウンドの地面に当たったら
	if(ball.getPoint().y - ball.getRectBox().height < objects->ground.getPoint().y){
		result_str = "hit";			// ヒット
		score += 2;					// スコアを2加算
		check_flag = false;			// もう調べない
		return;
	}

	// ボールがグラウンドの奥まで飛んだら
	if(ball.getPoint().z + ball.getRectBox().length < ground.getPoint().z - ground.getRectBox().length){
		result_str = "homerun";		// ホームラン
		score += 3;					// スコアを3加算
		check_flag = false;			// もう調べない
		return;
	}
}

void Game::hit_process()
{
	MyBall& ball = objects->ball;
	// ボールがグラウンドの地面に当たったら
	if(ball.getPoint().y - ball.getRectBox().height < objects->ground.getPoint().y){
		const Point3d& pt = ball.getPoint();
		ball.move(Point3d(pt.x, objects->ground.getPoint().y + ball.getRectBox().height, pt.z));
		const Vector3d& vec = ball.getVector();
		ball.setVector(vec.x, -vec.y, vec.z);
	}
}

IScene* Game::update()
{
	objects->update();

	// ボールが独立していたら
	if(objects->ball.getState() == MyBall::State::ISOLATED){
		// check_flagがたっていたら
		if(check_flag){
			check_ball();		// ボールを調べる
		}
		hit_process();			// ボールが地面に当たるときの処理
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
	/* 画面クリア */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/* モデル・ビュー変換行列の初期化 */
	glLoadIdentity();

	/* カメラのセット */
	camera->setCamera();

	/* 光源の位置を指定 */
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

	// ボールの残りの数を表示
	stringstream stream;
	stream << ball_num;
	glColor3d(0.0, 0.0, 1.0);
	glRasterPos3d(1.5, 2.0, 0.0);
	drawString("Ball:");
	drawString(stream.str().c_str());

	// スコアの表示
	stream.str("");		// バッファのクリア
	stream << score;
	glColor3d(0.0, 0.0, 1.0);
	glRasterPos3d(1.5, 1.5, 0.0);
	drawString("Score:");
	drawString(stream.str().c_str());

	// 結果の表示
	glColor3d(1.0, 0.0, 1.0);
	glRasterPos3d(1.7, 0.5, 0.0);
	drawString(result_str.c_str());

	glEnable(GL_LIGHTING);

//	glutSwapBuffers();			// GameDecorator側で出力させる
}

// ゲームを止める(この機能があるならGameDecorator側で止める必要はないかもしれない)
void Game::stop()
{
	usingDevice->resetEventHandlar();
}

// ゲームを再開する
void Game::restart()
{
	usingDevice->setEventHandlar();
}