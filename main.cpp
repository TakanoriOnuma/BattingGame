#include <stdlib.h>
#include <math.h>
#include <iostream>
#include "OpenGL.h"

using namespace std;

#include "DrawManager.h"
#include "KeyboardManager.h"
#include "MouseManager.h"
#include "MyBox.h"
#include "MyTeapot.h"
#include "MyRobot.h"
#include "MyCylinder.h"
#include "MySphere.h"
#include "MaterialData.h"
#include "RobotArm.h"
#include "MyBat.h"
#include "PitchingRobotArm.h"
#include "BattingRobot.h"

/* 定数を定義 */
#define PI 3.141592653589793	// π
#define ROUND_R  3.0			// 1周の半径
#define LEG_R1 30.0				// 足の股関節の最大角度
#define LEG_R2 20.0				// 足の膝関節の最大角度
#define ARM_R1 30.0				// 腕の肩関節の最大角度
#define ARM_R2 15.0				// 腕の肘関節の最大角度
#define STEPCYCLE 100			// 手足のひと振りに要するフレーム数
#define WALKCYCLE 1000			// ステージ場を1周するのに要するフレーム数
#define FRAME_TIME 40			// 1フレームにかかる時間

/* マクロを定義 */
#define DegToRad(Deg) (PI * (Deg) / 180)		// 度をラジアンへ
#define RadToDeg(Rad) (180 * (Rad) / PI)		// ラジアンを度へ

const double step_r = 2 * PI / STEPCYCLE;		// 手足の角速度
const double walk_r = 2 * PI / WALKCYCLE;		// 1周する角速度
bool  move_flag = false;						// 動いていいか

MyRobot*  robot;
RobotArm* robotArm;
MyBat*    bat;
PitchingRobotArm* pitchingRobotArm;
BattingRobot* battingRobot;

double angle = 0.0;

/*
 *	直方体を描く
 */
void myBox(double x, double y, double z)
{
	GLdouble hx = x * 0.5;
	GLdouble hz = z * 0.5;

	GLdouble vertex[][3] = {
		{ -hx,  -y, -hz },
		{  hx,  -y, -hz },
		{  hx, 0.0, -hz },
		{ -hx, 0.0, -hz },
		{ -hx,  -y,  hz },
		{  hx,  -y,  hz },
		{  hx, 0.0,  hz },
		{ -hx, 0.0,  hz },
	};

	static int face[][4] = {
		{ 0, 1, 2, 3 },
		{ 1, 5, 6, 2 },
		{ 5, 4, 7, 6 },
		{ 4, 0, 3, 7 },
		{ 4, 5, 1, 0 },
		{ 3, 2, 6, 7 },
	};

	static GLdouble normal[][3] = {
		{  0.0,  0.0, -1.0 },
		{  1.0,  0.0,  0.0 },
		{  0.0,  0.0,  1.0 },
		{ -1.0,  0.0,  0.0 },
		{  0.0, -1.0,  0.0 },
		{  0.0,  1.0,  0.0 },
	};

	static GLfloat red[] = { 0.8, 0.2, 0.2, 1.0 };

	/* 材質を設定する */
	glMaterialfv(GL_FRONT, GL_DIFFUSE, red);

	glBegin(GL_QUADS);
	for(int j = 0; j < 6; j++){
		glNormal3dv(normal[j]);
		for(int i = 3; i >= 0; i--){
			glVertex3dv(vertex[face[j][i]]);
		}
	}
	glEnd();
}

/*
 *	腕/足を描画
 */
void armleg(double girth, double length, double r1, double r2)
{
	glRotated(r1, 1.0, 0.0, 0.0);
	myBox(girth, length, girth);
	glTranslated(0.0, -0.05 - length, 0.0);
	glRotated(r2, 1.0, 0.0, 0.0);
	myBox(girth, length, girth);
}

/*
 *	地面を描く
 */
void myGround(double height, int width, int distance)
{
	static GLfloat ground[][4] = {
		{ 0.6, 0.6, 0.6, 1.0 },
		{ 0.3, 0.3, 0.3, 1.0 },
	};

	glBegin(GL_QUADS);
	glNormal3d(0.0, 1.0, 0.0);
	for(int j = -distance / 2; j < distance / 2; j++){
		for(int i = -width / 2; i < width / 2; i++){
			glMaterialfv(GL_FRONT, GL_DIFFUSE, ground[(i + j) & 1]);
			glVertex3d((GLdouble)i, height, (GLdouble)j);
			glVertex3d((GLdouble)i, height, (GLdouble)(j + 1));
			glVertex3d((GLdouble)(i + 1), height, (GLdouble)(j + 1));
			glVertex3d((GLdouble)(i + 1), height, (GLdouble)j);
		}
	}
	glEnd();
}

/*
 *	画面を表示する
 */
void display()
{
	/* 光源の位置 */
	static GLfloat lightpos0[] = { 3.0, 4.0, 5.0, 1.0 };
	static GLfloat lightpos1[] = {-3.0, 4.0, 5.0, 1.0 };

	/* フレーム数 */
	static int frame = 0;

	if(move_flag){		// 動いていいなら
		++frame;		// フレーム数をカウントをする
	}

	double ll1 = LEG_R1 * sin(step_r * frame);				// 箱男の左足の股関節の角度
	double ll2 = LEG_R2 * sin(step_r * frame) + LEG_R2;		// 箱男の左足の膝関節の角度

	double rl1 = LEG_R1 * sin(-step_r * frame);				// 箱男の右足の股関節の角度
	double rl2 = LEG_R2 * sin(-step_r * frame) + LEG_R2;	// 箱男の右足の膝関節の角度

	double la1 = ARM_R1 * sin(-step_r * frame);				// 箱男の左腕の肩関節
	double la2 = ARM_R2 * sin(-step_r * frame) - ARM_R2;	// 箱男の左腕の肘関節

	double ra1 = ARM_R1 * sin(step_r * frame);				// 箱男の右腕の肩関節
	double ra2 = ARM_R2 * sin(step_r * frame) - ARM_R2;		// 箱男の右腕の肘関節

	double px = -ROUND_R * cos(walk_r * frame);		// 箱男のx座標
	double pz = ROUND_R * sin(walk_r * frame);		// 箱男のz座標
	double r = RadToDeg(walk_r * frame);			// 箱男の向き
	double h = 0.0;									// 箱男の高さ

	/* 画面クリア */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/* モデル・ビュー変換行列の初期化 */
	glLoadIdentity();

	/* 視点の移動(物体の方を奥に移す) */
	glTranslated(0.0, 0.0, -10.0);

	glRotated(angle, 0.0, 1.0, 0.0);

	/* 光源の位置を指定 */
	glLightfv(GL_LIGHT0, GL_POSITION, lightpos0);
	glLightfv(GL_LIGHT1, GL_POSITION, lightpos1);


	DrawManager::getDrawManager().draw();

	/* シーンの描画 */
	/* 地面 */
	myGround(-1.8, 10, 10);

	/* 箱男の位置と方向 */
	glTranslated(px, h, pz);
	glRotated(r, 0.0, 1.0, 0.0);

	/* 頭 */
	myBox(0.20, 0.25, 0.22);

	/* 胴 */
	glTranslated(0.0, -0.3, 0.0);
	myBox(0.4, 0.6, 0.3);

	/* 左足 */
	glPushMatrix();
	glTranslated(0.1, -0.65, 0.0);
	armleg(0.2, 0.4, ll1, ll2);
	glPopMatrix();

	/* 右足 */
	glPushMatrix();
	glTranslated(-0.1, -0.65, 0.0);
	armleg(0.2, 0.4, rl1, rl2);
	glPopMatrix();

	/* 左腕 */
	glPushMatrix();
	glTranslated(0.28, 0.0, 0.0);
	armleg(0.16, 0.4, la1, la2);
	glPopMatrix();

	/* 右腕 */
	glPushMatrix();
	glTranslated(-0.28, 0.0, 0.0);
	armleg(0.16, 0.4, ra1, ra2);
	glPopMatrix();

	glutSwapBuffers();
}

void mouse(int button, int state, int x, int y)
{
	/* 左クリックをしているか */
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
		move_flag = !move_flag;		// フラグを反転させる
	}
}

void resize(int w, int h)
{
	/* ウィンドウ全体をビューポートにする */
	glViewport(0, 0, w, h);

	/* 透視変換行列の指定 */
	glMatrixMode(GL_PROJECTION);

	/* 透視変換行列の初期化 */
	glLoadIdentity();

	gluPerspective(30.0, (double)w / h, 1.0, 100.0);

	/* モデル・ビュー変換行列の指定 */
	glMatrixMode(GL_MODELVIEW);
}


void check_keyboard()
{
	KeyboardManager& keyboardManager = KeyboardManager::getKeyboardManager();

	
	if(keyboardManager.isPushCharKey('\033') || keyboardManager.isPushCharKey('q')){
		exit(0);
	}
	
	if(keyboardManager.isPushCharKey('a')){
		angle += 1.0;
	}
	else if(keyboardManager.isPushCharKey('d')){
		angle -= 1.0;
	}

	if(keyboardManager.isPushCharKey('i')){
		robotArm->addArmAngle(1.0);
	}
	else if(keyboardManager.isPushCharKey('k')){
		robotArm->addArmAngle(-1.0);
	}

	if(keyboardManager.isPushCharKey('o')){
		pitchingRobotArm->ball_throw();
	}

	if(keyboardManager.isPushCharKey('t')){
		battingRobot->swing();
	}


//	if(keyboardManager.isPushCharKey(' ')){
//		const Point2i& pt = MouseManager::getMouseManager().getMousePoint();
//		cout << "Mouse Point:(" << pt.x << ", " << pt.y << ")" << endl;
//	}
/*
	switch(key){
	case 'a':
		angle += 1.0;
		glutPostRedisplay();
		break;
	case 'd':
		angle -= 1.0;
		glutPostRedisplay();
		break;

	case 'i':
		robotArm->addArmAngle(1.0);
		glutPostRedisplay();
		break;
	case 'k':
		robotArm->addArmAngle(-1.0);
		glutPostRedisplay();
		break;

	}
*/
}

void check_specialKeyboard()
{
	KeyboardManager& keyboardManager = KeyboardManager::getKeyboardManager();

	if(keyboardManager.isPushSpecialKey(SpecialKey::UP)){
		if(keyboardManager.isPushCharKey('r')){
			robot->run();
		}
		else{
			robot->walk();
		}
	}
	else if(keyboardManager.isPushSpecialKey(SpecialKey::DOWN)){
		robot->walk();
	}
	
	if(keyboardManager.isPushSpecialKey(SpecialKey::LEFT)){
		robot->addAngle(-5.0);
	}
	else if(keyboardManager.isPushSpecialKey(SpecialKey::RIGHT)){
		robot->addAngle(5.0);
	}

/*
	switch(key){
	case GLUT_KEY_UP:
//		robot->move(Vector3d(0.0, 0.0, -0.1));
		robot->walk();
		break;
	case GLUT_KEY_DOWN:
//		robot->move(Vector3d(0.0, 0.0, 0.1));
		robot->walk();
		break;
	case GLUT_KEY_LEFT:
//		robot->move(Vector3d(-0.1, 0.0, 0.0));
		robot->addAngle(-5.0);
		break;
	case GLUT_KEY_RIGHT:
//		robot->move(Vector3d(0.1, 0.0, 0.0));
		robot->addAngle(5.0);
		break;
	}
*/
}


void timer(int t)
{
	check_keyboard();
	check_specialKeyboard();

	robot->update();
	pitchingRobotArm->update();
	battingRobot->update();

	glutPostRedisplay();
	glutTimerFunc(t, timer, FRAME_TIME);
}


void init()
{
	/* 初期設定 */
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);

	// --- 透過の設定 --- //
//	glEnable(GL_BLEND);
//	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// 光源の特性の配列を宣言
	GLfloat light_ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f },
		light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f },
		light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };	

	// 最初の光源の特性指定
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	// 次の光源の特性指定
	glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular);

	DrawManager& drawManager = DrawManager::getDrawManager();

	robot = new MyRobot();
	robot->setMaterialData(MaterialData::createMaterialData(Color::WHITE, Material::PLASTIC));
	drawManager.setDrawObject(robot);

	DrawObject* obj;
	obj = new MyCylinder(1.5, -1.0, 1.5, 0.5, 0.8, 16);
	obj->setMaterialData(MaterialData::createMaterialData(Jewel::EMERALD));
	obj->setRotateVector(1.0, 0.0, 0.0);
	obj->setAngle(-30.0);
	drawManager.setDrawObject(obj);
	obj = new MyCylinder(1.5, -1.0, -1.5, 0.7, 0.7);
	obj->setMaterialData(MaterialData::createMaterialData(Jewel::TURQUOISE));
	obj->setRotateVector(1.0, 1.0, 0.0);
	obj->setAngle(20.0);
	drawManager.setDrawObject(obj);
	obj = new MySphere(-1.5, -1.0, 1.5, 0.8, 64);
	obj->setMaterialData(MaterialData::createMaterialData(Jewel::OBSIDIAN));
	drawManager.setDrawObject(obj);
	obj = new MyTeapot(-1.5, -1.0, -1.5);
	obj->setMaterialData(MaterialData::createMaterialData(Jewel::RUBY));
	drawManager.setDrawObject(obj);

	robotArm = new RobotArm(0.0, -1.5, -3.0);
	robotArm->setMaterialData(MaterialData::createMaterialData(Ore::COPPER));
	drawManager.setDrawObject(robotArm);

	pitchingRobotArm = new PitchingRobotArm(2.0, -1.5, -3.0);
	pitchingRobotArm->setMaterialData(MaterialData::createMaterialData(Ore::BRONZE));
	drawManager.setDrawObject(pitchingRobotArm);


	battingRobot = new BattingRobot(0.0, 0.0, 1.0);
	battingRobot->setMaterialData(MaterialData::createMaterialData(Jewel::TURQUOISE));
	drawManager.setDrawObject(battingRobot);

	robot = battingRobot;

	bat = new MyBat(3.0, -1.0, 3.0);
	bat->setMaterialData(MaterialData::createMaterialData(Ore::GOLD));
	bat->setRotateVector(1.0, -1.0, 0.0);
	bat->setAngle(45.0);
	drawManager.setDrawObject(bat);
}

void keyboard(unsigned char key, int x, int y)
{
	/* ESC か q をタイプしたら終了 */
	if(key == '\033' || key == 'q'){
		exit(0);
	}

	if(key == ' '){
		MouseManager& mouseManager = MouseManager::getMouseManager();
		const Point2i& pt = mouseManager.getMousePoint();
		cout << "Mouse Point:(" << pt.x << ", " << pt.y << ")" << endl;
		cout << "--- Mouse State ---" << endl;
		cout << boolalpha;
		cout << " LEFT:" << mouseManager.isClick(MouseClick::LEFT) << endl;
		cout << " MIDDLE:" << mouseManager.isClick(MouseClick::MIDDLE) << endl;
		cout << " RIGHT:" << mouseManager.isClick(MouseClick::RIGHT) << endl;
		cout << "-------------------" << endl;
	}
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitWindowSize(400, 300);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutCreateWindow(argv[0]);
	glutDisplayFunc(display);
	glutReshapeFunc(resize);
//	glutMouseFunc(mouse);


//	glutKeyboardFunc(keyboard);
//	glutSpecialFunc(specialKeyboard);

	KeyboardManager::getKeyboardManager().useCharKeyboard();
	KeyboardManager::getKeyboardManager().useSpecialKeyboard();
	KeyboardManager::getKeyboardManager().setKeyboardHandlar(keyboard);

	MouseManager::getMouseManager().useMouse();
	MouseManager::getMouseManager().setMouseHandlar(mouse);

	glutTimerFunc(0, timer, FRAME_TIME);
	init();
	glutMainLoop();
	return 0;
}