#include "OpenGL.h"

#include "MouseManager.h"

// ----- friend�֐��̒�` ----- //
void _passive(int x, int y)
{
	MouseManager& mouseManager = MouseManager::getMouseManager();

	if(mouseManager.passive_handlar != NULL){
		mouseManager.passive_handlar(x, y);
	}
	mouseManager.pt.x = x;
	mouseManager.pt.y = y;
}

// �N���b�N��E�B���h�E�O�ɏo��΃E�B���h�E�O�̍��W�𓾂Ă��܂�
void _motion(int x, int y)
{
	MouseManager& mouseManager = MouseManager::getMouseManager();

	if(mouseManager.motion_handlar != NULL){
		mouseManager.motion_handlar(x, y);
	}
	mouseManager.pt.x = x;
	mouseManager.pt.y = y;
}

void _mouse(int button, int state, int x, int y)
{
	MouseManager& mouseManager = MouseManager::getMouseManager();

	if(mouseManager.mouse_handlar != NULL){
		mouseManager.mouse_handlar(button, state, x, y);
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


// ===== MouseManager�̃����o�֐��̒�` ===== //
MouseManager::MouseManager()
	: passive_handlar(NULL), motion_handlar(NULL), mouse_handlar(NULL)
{
}

// �֐��ɓ����ϐ����������ăV���O���g������������
MouseManager& MouseManager::getMouseManager()
{
	static MouseManager mouseManager;
	return mouseManager;
}

void MouseManager::useMouse()
{
	glutPassiveMotionFunc(_passive);
	glutMotionFunc(_motion);
	glutMouseFunc(_mouse);
}