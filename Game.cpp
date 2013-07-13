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
	MyBall ball;
	Ground ground;
	BattingRobot battingRobot;
	PitchingRobotArm pitchingRobotArm;

	Rectangle2D batting_field;
	MyCircle circle;

	DrawableObjects()
		: ball(0.2),
		ground(0.0, -1.8, -7.0, 10, 25),
		battingRobot(-2.3, 0.9, 3.0),
		pitchingRobotArm(0.0, -1.5, -15.0),
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

	// 必要のあるものだけupdateする
	void update(){
		ball.update();
		battingRobot.update();
		pitchingRobotArm.update();
	}
};


// ===== マウス入力のイベント処理 ===== //
class Game::GameMouseListener : public MouseListener
{
	Game& parent;

public:
	GameMouseListener(Game& game) : parent(game)
	{
		MouseManager::getInstance().addListener(this);
	}

	~GameMouseListener(){
		MouseManager::getInstance().removeListener(this);
	}

	void passive(int x, int y) override{
		// Zバッファを用いて3次元座標を得るため、
		// ディスプレイには表示しなくても長方形を描いてそこに当たるようにする。
		glLoadIdentity();				// 一度初期化する
		parent.camera->setCamera();		// cameraの設定を行う
		parent.objects->batting_field.drawField();		// フィールドを描かせる
		Point3d worldPoint = MouseManager::getInstance().getWorldPoint3d();

		const Point3d& field_pt = parent.objects->batting_field.getPoint();
		const Rectangle2D& field = parent.objects->batting_field;
		if(worldPoint.x > field_pt.x - field.getWidth() / 2 &&
			worldPoint.x < field_pt.x + field.getWidth() / 2 &&
			worldPoint.y > field_pt.y - field.getHeight() / 2 &&
			worldPoint.y < field_pt.y + field.getHeight() / 2){
				parent.objects->circle.move(worldPoint);
		}
	}

	void motion(int x, int y) override{
	}

	void mouse(int button, int state, int x, int y) override{
		if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
			parent.objects->battingRobot.swing(parent.objects->circle.getPoint());
		}
	}

	void wheel(int wheel_number, int direction, int x, int y) override{
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
	mouseListener = new GameMouseListener(*this);
	hitProcesser = NoDelayHitProcesser::getInstance();

	emitionListener = new EmitionListener(*this);
	objects->ball.setEmitionMessage(emitionListener);
}

Game::~Game()
{
	delete objects;
	delete camera;
	delete mouseListener;

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
		camera->addDistance(-1.0);
	}
	else if(keyboardManager.isPushCharKey('s')){
		camera->addDistance(1.0);
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

	// ボールがグラウンドの脇の外へ出たら
	if(ball.getPoint().x < ground.getPoint().x - ground.getRectBox().width / 2 ||
		ball.getPoint().x > ground.getPoint().x + ground.getRectBox().width / 2){
			result_str = "foul";	// ファウル
			score += 1;				// スコアを1加算
			check_flag = false;		// もう調べない
			return;
	}

	// ボールがグラウンドの地面に当たったら
	if(ball.getPoint().y - ball.getRectBox().height < objects->ground.getPoint().y){
		result_str = "hit";			// ヒット
		cout << "reflect" << endl;
		const Point3d& pt = ball.getPoint();
		ball.move(Point3d(pt.x, objects->ground.getPoint().y + ball.getRectBox().height, pt.z));
		outPoint("ball.point", pt);
		const Vector3d& vec = ball.getVector();
		ball.setVector(vec.x, -vec.y, vec.z);
		outVector("ball.vec", vec);
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

IScene* Game::update()
{
	objects->update();

	// ボールが独立していて、check_flagがたっていたら
	if(objects->ball.getState() == MyBall::State::ISOLATED && check_flag){
		check_ball();		// ボールを調べる
	}

	check_char_key();
	check_special_key();

	hitProcesser->hitProcess(objects->ball, objects->battingRobot);

	return this;
}


void Game::display() const
{
	static GLfloat lightpos0[] = { 3.0, 4.0, 5.0, 1.0 };
	static GLfloat lightpos1[] = {-3.0, 4.0, 5.0, 1.0 };
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
	MouseManager::getInstance().removeListener(mouseListener);
}

// ゲームを再開する
void Game::restart()
{
	MouseManager::getInstance().addListener(mouseListener);
}