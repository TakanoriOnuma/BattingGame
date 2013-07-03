#include <algorithm>

#include "OpenGL.h"

#include "MouseManager.h"

using namespace std;

// ----- friend関数の定義 ----- //
void _passive(int x, int y)
{
	MouseManager& mouseManager = MouseManager::getInstance();

	if(mouseManager.passive_handlar != NULL){
		mouseManager.passive_handlar(x, y);
	}

	for each (MouseListener* listener in mouseManager.listeners){
		listener->passive(x, y);
	}

	mouseManager.pt.x = x;
	mouseManager.pt.y = y;
}

// クリック後ウィンドウ外に出ればウィンドウ外の座標を得てしまう
void _motion(int x, int y)
{
	MouseManager& mouseManager = MouseManager::getInstance();

	if(mouseManager.motion_handlar != NULL){
		mouseManager.motion_handlar(x, y);
	}

	for each (MouseListener* listener in mouseManager.listeners){
		listener->motion(x, y);
	}

	mouseManager.pt.x = x;
	mouseManager.pt.y = y;
}

void _mouse(int button, int state, int x, int y)
{
	MouseManager& mouseManager = MouseManager::getInstance();

	if(mouseManager.mouse_handlar != NULL){
		mouseManager.mouse_handlar(button, state, x, y);
	}

	for each (MouseListener* listener in mouseManager.listeners){
		listener->mouse(button, state, x, y);
	}

	switch(button){
	case GLUT_LEFT_BUTTON:
		if(state == GLUT_DOWN){
			mouseManager.state.set(static_cast<size_t>(MouseClick::LEFT));
		}
		else if(state == GLUT_UP){
			mouseManager.state.reset(static_cast<size_t>(MouseClick::LEFT));
		}
		break;
	case GLUT_MIDDLE_BUTTON:
		if(state == GLUT_DOWN){
			mouseManager.state.set(static_cast<size_t>(MouseClick::MIDDLE));
		}
		else if(state == GLUT_UP){
			mouseManager.state.reset(static_cast<size_t>(MouseClick::MIDDLE));
		}
		break;
	case GLUT_RIGHT_BUTTON:
		if(state == GLUT_DOWN){
			mouseManager.state.set(static_cast<size_t>(MouseClick::RIGHT));
		}
		else if(state == GLUT_UP){
			mouseManager.state.reset(static_cast<size_t>(MouseClick::RIGHT));
		}
		break;
	}
}

void _wheel(int wheel_number, int direction, int x, int y)
{
	MouseManager& mouseManager = MouseManager::getInstance();

	if(mouseManager.wheel_handlar != NULL){
		mouseManager.wheel_handlar(wheel_number, direction, x, y);
	}

	for each (MouseListener* listener in mouseManager.listeners){
		listener->wheel(wheel_number, direction, x, y);
	}
}


// ===== MouseManagerのメンバ関数の定義 ===== //
MouseManager::MouseManager()
	: passive_handlar(NULL), motion_handlar(NULL), mouse_handlar(NULL)
{
}

// 関数に内部変数を持たせてシングルトンを実装する
MouseManager& MouseManager::getInstance()
{
	static MouseManager mouseManager;
	return mouseManager;
}

void MouseManager::useMouse()
{
	glutPassiveMotionFunc(_passive);
	glutMotionFunc(_motion);
	glutMouseFunc(_mouse);
	glutMouseWheelFunc(_wheel);
}

void MouseManager::addListener(MouseListener* listener){
	vector<MouseListener*>::iterator pos =
		find(listeners.begin(), listeners.end(), listener);

	// 登録されていなかったら
	if(pos == listeners.end()){
		listeners.push_back(listener);
	}
}

void MouseManager::removeListener(MouseListener* listener){
	vector<MouseListener*>::iterator end_it =
		remove(listeners.begin(), listeners.end(), listener);

	listeners.erase(end_it, listeners.end());
}

Point3d MouseManager::getWorldPoint3d() const
{
	GLdouble model[16], proj[16];
    GLint view[4];
    GLfloat z;

	Point3d worldPoint3d;

	glGetDoublev(GL_MODELVIEW_MATRIX, model);
	glGetDoublev(GL_PROJECTION_MATRIX, proj);
	glGetIntegerv(GL_VIEWPORT, view);

	int h = glutGet(GLUT_WINDOW_HEIGHT);

	glReadPixels(pt.x, h - pt.y, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &z);
	gluUnProject(pt.x, h - pt.y, z, model, proj, view,
		&worldPoint3d.x, &worldPoint3d.y, &worldPoint3d.z);

	return worldPoint3d;
}