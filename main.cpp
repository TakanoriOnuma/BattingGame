#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <time.h>
#include "OpenGL.h"

using namespace std;

#include "KeyboardManager.h"
#include "MouseManager.h"
#include "SceneManager.h"
#include "StartMenu.h"
#include "Game.h"
#include "XorShift.h"

void resize(int w, int h)
{
	/* �E�B���h�E�S�̂��r���[�|�[�g�ɂ��� */
	glViewport(0, 0, w, h);

	/* �����ϊ��s��̎w�� */
	glMatrixMode(GL_PROJECTION);

	/* �����ϊ��s��̏����� */
	glLoadIdentity();

	gluPerspective(30.0, (double)w / h, 1.0, 100.0);

	/* ���f���E�r���[�ϊ��s��̎w�� */
	glMatrixMode(GL_MODELVIEW);
}

void init()
{
	/* �����ݒ� */
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);

	// �����̓����̔z���錾
	GLfloat light_ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f },
		light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f },
		light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };	

	// �ŏ��̌����̓����w��
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	// ���̌����̓����w��
	glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular);

	XorShift::instance().setSeed(static_cast<unsigned int>(time(NULL)));

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void keyboard(unsigned char key, int x, int y)
{
	/* ESC �� q ���^�C�v������I�� */
	if(key == '\033' || key == 'q'){
		exit(0);
	}

	if(key == ' '){
		MouseManager& mouseManager = MouseManager::getInstance();
		const Point2i& pt = mouseManager.getMousePoint();
		Point3d worldPoint3d = mouseManager.getWorldPoint3d();
		cout << "Mouse Point:(" << pt.x << ", " << pt.y << ")" << endl;
		cout << "World Point:(" << worldPoint3d.x << ", " << worldPoint3d.y << ", " << worldPoint3d.z << ")" << endl;
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
	glutReshapeFunc(resize);

	KeyboardManager::getInstance().useCharKeyboard();
	KeyboardManager::getInstance().useSpecialKeyboard();
	KeyboardManager::getInstance().setKeyboardHandlar(keyboard);

	MouseManager::getInstance().useMouse();

	SceneManager::getInstance().setScene(new Game());

	init();
	glutMainLoop();
	return 0;
}