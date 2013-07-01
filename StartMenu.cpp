#include "StartMenu.h"
#include "MyTeapot.h"
#include "MyCylinder.h"
#include "Ground.h"
#include "MaterialData.h"
#include "Camera.h"
#include "Game.h"
#include "KeyboardManager.h"
#include "MouseManager.h"

struct StartMenu::DrawableObjects{
	MyTeapot   teapot;
	MyCylinder cyliender;
	Ground     ground;

	DrawableObjects()
		: teapot(),
		cyliender(0.0, 0.0, -3.0, 1.0, 2.0),
		ground(0.0, -1.0, 0.0)
	{
		teapot.setMaterialData(MaterialData::createMaterialData(Jewel::RUBY));

		cyliender.setMaterialData(MaterialData::createMaterialData(Ore::CHROME));
		cyliender.setRotateVector(1.0, 1.0, 0.0);
		cyliender.addAngle(45.0);
	}

	void draw() const{
		teapot.draw(true, true);
		cyliender.draw(true, true);
		ground.draw(true, true);
	}
};


class StartMenu::StartMenuMouseListener : public MouseListener
{
	StartMenu& parent;

	Point2i oldPos;

public:
	StartMenuMouseListener(StartMenu& parent) : parent(parent)
	{
		MouseManager::getInstance().addListener(this);
	}

	~StartMenuMouseListener(){
		MouseManager::getInstance().removeListener(this);
	}

	void passive(int x, int y) override{
	}

	void motion(int x, int y) override{
		if(MouseManager::getInstance().isClick(MouseClick::LEFT)){
			parent.camera->addAngle_xz(x - oldPos.x);
			parent.camera->addAngle_yz(y - oldPos.y);

			oldPos.x = x;
			oldPos.y = y;
		}
	}

	void mouse(int button, int state, int x, int y) override{
		if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
			oldPos.x = x;
			oldPos.y = y;
		}
	}

	void wheel(int wheel_number, int direction, int x, int y) override{
		parent.camera->addDistance(-direction);
	}
};


StartMenu::StartMenu()
	: angle_xz(0.0), angle_yz(0.0)
{
	objects = new DrawableObjects();
	camera  = new Camera();
	mouseListener = new StartMenuMouseListener(*this);
}

StartMenu::~StartMenu()
{
	delete objects;
	delete camera;
	delete mouseListener;
}

void StartMenu::check_char_key()
{
	KeyboardManager& keyboardManager = KeyboardManager::getInstance();

	if(keyboardManager.isPushCharKey('a')){
		objects->teapot.setMaterialData(MaterialData::createMaterialData(Jewel::EMERALD));
	}
	else if(keyboardManager.isPushCharKey('s')){
		objects->teapot.setMaterialData(MaterialData::createMaterialData(Jewel::JADE));
	}
	else if(keyboardManager.isPushCharKey('d')){
		objects->teapot.setMaterialData(MaterialData::createMaterialData(Jewel::OBSIDIAN));
	}
	else if(keyboardManager.isPushCharKey('f')){
		objects->teapot.setMaterialData(MaterialData::createMaterialData(Jewel::PEARL));
	}
	else if(keyboardManager.isPushCharKey('g')){
		objects->teapot.setMaterialData(MaterialData::createMaterialData(Jewel::RUBY));
	}
	else if(keyboardManager.isPushCharKey('h')){
		objects->teapot.setMaterialData(MaterialData::createMaterialData(Jewel::TURQUOISE));
	}

	if(keyboardManager.isPushCharKey('z')){
		camera->getEye().x += 0.1;
	}
	else if(keyboardManager.isPushCharKey('x')){
		camera->getEye().x -= 0.1;
	}

	if(keyboardManager.isPushCharKey('n')){
		camera->getTarget().x += 0.1;
	}
	else if(keyboardManager.isPushCharKey('m')){
		camera->getTarget().x -= 0.1;
	}

	if(keyboardManager.isPushCharKey('o')){
		camera->addAngle_yz(1.0);
	}
	else if(keyboardManager.isPushCharKey('p')){
		camera->addAngle_yz(-1.0);
	}
}

void StartMenu::check_special_key()
{
	KeyboardManager& keyboardManager = KeyboardManager::getInstance();

	if(keyboardManager.isPushSpecialKey(SpecialKey::LEFT)){
		angle_xz -= 2.0;
	}
	else if(keyboardManager.isPushSpecialKey(SpecialKey::RIGHT)){
		angle_xz += 2.0;
	}

	if(keyboardManager.isPushSpecialKey(SpecialKey::UP)){
		angle_yz -= 2.0;
	}
	else if(keyboardManager.isPushSpecialKey(SpecialKey::DOWN)){
		angle_yz += 2.0;
	}
}

IScene* StartMenu::update()
{
	check_char_key();
	check_special_key();

	if(KeyboardManager::getInstance().isPushCharKey(' ')){
		return new Game();
	}

	return this;
}

void StartMenu::display() const
{
	static GLfloat lightpos0[] = { 3.0, 4.0, 5.0, 1.0 };
	static GLfloat lightpos1[] = {-3.0, 4.0, 5.0, 1.0 };
	/* 画面クリア */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/* モデル・ビュー変換行列の初期化 */
	glLoadIdentity();

	camera->setCamera();		// カメラをセット


	/* 光源の位置を指定 */
	glLightfv(GL_LIGHT0, GL_POSITION, lightpos0);
	glLightfv(GL_LIGHT1, GL_POSITION, lightpos1);

	objects->draw();

	glutSwapBuffers();
}