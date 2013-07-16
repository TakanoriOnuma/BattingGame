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
#include "GameDecorator.h"
#include "XorShift.h"

void resize(int w, int h)
{
	/* �E�B���h�E�S�̂��r���[�|�[�g�ɂ��� */
	glViewport(0, 0, w, h);

	/* �����ϊ��s��̎w�� */
	glMatrixMode(GL_PROJECTION);

	/* �����ϊ��s��̏����� */
	glLoadIdentity();

	gluPerspective(30.0, (double)w / h, 1.0, 200.0);

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
}

void explain()
{
	cout << "�� Batting Game ��" << endl;
	cout << "----- ��{���[�� -----" << endl;
	cout << "�E���ɂ��郍�{�b�g�A�[�����Ԃ��g�̒��ɖڊ|���ă{�[���𓊂��Ă��܂��B" << endl;
	cout << "�E�ΐF�̊ۂ��J�[�\���ƃ{�[�����d�Ȃ����Ƃ��o�b�g��U���Ă����\n�@�{�[����ł��Ԃ����Ƃ��o���܂��B" << endl;
	cout << "�E�ł��Ԃ��ꂽ�{�[�����������ꏊ�ɂ���ĉ��_�����X�R�A���ω����܂��B" << endl;
	cout << "�E�S����10�������āA�o���邾�������X�R�A��ڎw���܂��B" << endl;
	cout << "----------------------" << endl;

	cout << '\n';
	cout << "----- ���_�����X�R�A�ɂ��� -----" << endl;
	cout << "�E���_�����X�R�A�ɂ̓t�@�[��(foul)�A�q�b�g(hit)�A\n�@�z�[������(homerun)������܂��B" << endl;
	cout << "�E�t�@�[��(foul)�́A��̓I�ɐ��͈����Ă��܂��񂪁A\n�@���܂�e�̕��֏o��ƃt�@�[���ƂȂ�A���_��1�_�ł��B" << endl;
	cout << "�E�q�b�g(hit)�́A�{�[����ł��Ԃ��Ă��āA\n�@�t�@�[���ł��z�[�������ł��Ȃ����̂��q�b�g�ƂȂ�A���_��2�_�ł��B" << endl;
	cout << "�E�z�[�������͉��ɂ���ǂ��z����ƃz�[�������ƂȂ�A���_��3�_�ł��B" << endl;
	cout << "�@�������A�ǂ̊O����ʂ����Ƃ��Ă��A�t�@�[���Ƃ͂Ȃ�Ȃ��ꍇ������A\n�@�z�[�������ƂȂ�ꍇ������܂��B" << endl;
	cout << "�E��U��(strike)�̏ꍇ�͓_���͉��_����܂���" << endl;
	cout << "------------------------------------" << endl;

	cout << '\n';
	cout << "----- �g�p����L�[ -----" << endl;
	cout << "���{�[���𓊂���֌W" << endl;
	cout << "�@t:" << "�{�[���𓊂���" << endl;
	cout << "�@y:" << "�{�[�����Z�b�g����(���������Ƃ��̃L�[�������Ȃ��Ǝ��̃{�[���𓊂����Ȃ�)" << endl;
	cout << "�@r:" << "�X�R�A�Ǝc��̃{�[���̐������Z�b�g����" << endl;
	cout << "���Q�[���̏����n" << endl;
	cout << "�@p:" << "�|�[�Y����" << endl;
	cout << "�@q:" << "�Q�[�����I������(ESC�ł��������ʂ�����)" << endl;
	cout << "����Փx���ߌn" << endl;
	cout << "�@1:" << "��Փx���ȒP(easy)�ɂ���" << endl;
	cout << "�@2:" << "��Փx�𕁒�(normal)�ɂ���" << endl;
	cout << "���o�b�e�B���O�t�B�[���h(�Ԃ��g)�֌W" << endl;
	cout << "�@8:" << "�o�b�e�B���O�t�B�[���h(�Ԃ��g)����������" << endl;
	cout << "�@9:" << "�o�b�e�B���O�t�B�[���h(�Ԃ��g)���L������" << endl;
	cout << "���g�p����f�o�C�X�֌W" << endl;
	cout << "�@m:" << "�}�E�X���g�p����" << endl;
	cout << "�@k:" << "�L�[�{�[�h���g�p����" << endl;
	cout << "�������蔻��֌W" << endl;
	cout << "�@z:" << "�x������̓����蔻��" << endl;
	cout << "�@x:" << "�x���Ȃ��̓����蔻��" << endl;
	cout << "���J�����֌W" << endl;
	cout << "�@a:" << "�����ɉ�荞��ł���" << endl;
	cout << "�@d:" << "�E���ɉ�荞��ł���" << endl;
	cout << "�@w:" << "�㑤�ɉ�荞��ł���" << endl;
	cout << "�@s:" << "�����ɉ�荞��ł���" << endl;
	cout << "�@n:" << "�߂Â��Ă���" << endl;
	cout << "�@f:" << "���̂��Ă���" << endl;
	cout << "-------------------------" << endl;

	cout << '\n';
	cout << "----- ��Փx�ɂ��� -----" << endl;
	cout << "�E�ȒP(easy)�ł́A�X���[�{�[���ƃX�g���[�g�𓊂��܂��B" << endl;
	cout << "�@���x�̍�������قǂȂ������܂œ���Ȃ��Ǝv���܂��B\n�@������3�����Ƃ������Ƃ�����A" << endl;
	cout << "�@�Ȃ��Ȃ����������͂߂Ȃ����Ǝv���܂����A����͊���邵������܂���B" << endl;
	cout << "�E����(normal)�ł́A�X���[�{�[���ƃX�g���[�g�ɉ����āA�J�[�u�������܂��B" << endl;
	cout << "�@���x�̍������Ȃ肠��A�ł��ɂ�����������܂���B\n�@�J�[�u�͕ω��̗ʂ����Ȃ�傫���A" << endl;
	cout << "�@�����܂ł͑S���łĂȂ���������܂���B" << endl;
	cout << "�@'8'�L�[�������ăo�b�e�B���O�t�B�[���h(�Ԃ��g)����������̂���ł��B" << endl;
	cout << "--------------------------" << endl;

	cout << '\n';
	cout << "----- �g�p�ł���f�o�C�X�ɂ��� -----" << endl;
	cout << "��{�I�ɂ̓}�E�X���g���ăQ�[�������邱�Ƃ����߂܂����A" << endl;
	cout << "�m�[�g�p�\�R���̂悤�Ƀ^�b�`�p�b�h���g����\n�Q�[��������Ƃ��ɂ����ꍇ������܂��B" << endl;
	cout << "�����ŃL�[�{�[�h�ł��Q�[�����o����悤�ɂ��܂����B" << endl;
	cout << "�g�p����f�o�C�X���}�E�X��L�[�{�[�h�ɂ�����@��" << endl;
	cout << "��L�ɂ���\"�g�p����L�[\"��\"�g�p����f�o�C�X�֌W\"�̂Ƃ�����Q�Ƃ��Ă��������B" << endl;
	cout << "--------------------------------------" << endl;

	cout << '\n';
	cout << "----- �o�b�g��U����@�A�J�[�\��(�ΐF�̉~)�𓮂������@ -----" << endl;
	cout << "���}�E�X���g�p" << endl;
	cout << "�@�o�b�g��U��:���N���b�N" << endl;
	cout << "�@�J�[�\���𓮂���:�o�b�e�B���O�t�B�[���h(�Ԃ��g)���Ń}�E�X�J�[�\���𓮂���" << endl;
	cout << "���L�[�{�[�h���g�p" << endl;
	cout << "�@�o�b�g��U��:�X�y�[�X�L�[" << endl;
	cout << "�@�J�[�\���𓮂���:���L�[" << endl;
	cout << "------------------------------------------------------------" << endl;

	cout << '\n';
	cout << "----- �����蔻��ɂ��� -----" << endl;
	cout << "�{���Ȃ�o�b�g�ƃ{�[���������������Ƀ{�[����ł��Ԃ��ׂ��ł����A" << endl;
	cout << "�Q�[�����ǂ����Ă��{�[�����J�[�\��(�ΐF�̉~)�ɗ������Ƀo�b�g��U���Ă��܂��A" << endl;
	cout << "��U������Ă��܂��ꍇ�������ł��B" << endl;
	cout << "���̂��߁A�o�b�g��U��Ɠ��͂��Ă�����\n�����蔻����s�����@���o����悤�ɂ��܂����B" << endl;
	cout << "����͋N�������炻�̂悤�ɂȂ��Ă��܂��B" << endl;
	cout << "�����ƃo�b�g�ƃ{�[����������^�C�~���O�œ����蔻����������ꍇ��" << endl;
	cout << "'z'�L�[����͂���Ώo���܂��B" << endl;
	cout << "�N�������炠��@�\�ɖ߂������ꍇ��'x'�L�[�������ĉ������B" << endl;
	cout << "------------------------------" << endl;

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

	SceneManager::getInstance().setScene(new GameDecorator());

	init();
	explain();
	glutMainLoop();
	return 0;
}