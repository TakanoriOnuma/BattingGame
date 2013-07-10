#include "GameDecorator.h"
#include "Game.h"
#include "Camera.h"
#include "KeyboardListener.h"
#include "KeyboardManager.h"

static void drawString(const char* str)
{
	while(*str != '\0'){
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *str);
		++str;
	}
}

class GameDecorator::GameDecoratorKeyboardListener : public KeyboardListener
{
	GameDecorator& parent;

public:
	GameDecoratorKeyboardListener(GameDecorator& parent) : parent(parent)
	{
		KeyboardManager::getInstance().addListener(this);
	}
	~GameDecoratorKeyboardListener()
	{
		KeyboardManager::getInstance().removeListener(this);
	}

	void keyboard(unsigned char key, int x, int y) override
	{
		if(key == 'p'){
			parent.pause_flag = !parent.pause_flag;		// �t���O�𔽓]������

			if(parent.pause_flag){			// �|�[�Y�t���O�������
				parent.game->stop();		// �Q�[�����~�߂�
			}
			else{							// �t���O���Ȃ����
				parent.game->restart();		// �Q�[�����ĊJ����
			}
		}
	}

	void keyboardUp(unsigned char key, int x, int y) override
	{
	}
	void specialKeyboard(int key, int x, int y) override
	{
	}
	void specialKeyboardUp(int key, int x, int y) override
	{
	}
};

GameDecorator::GameDecorator()
{
	pause_flag = false;
	game = new Game();
	camera = new Camera();
	keyboardListener = new GameDecoratorKeyboardListener(*this);
}

GameDecorator::~GameDecorator()
{
	delete game;
	delete keyboardListener;
}

IScene* GameDecorator::update()
{
	// pause�t���O�������Ă��Ȃ�������update����
	if(!pause_flag){
		IScene* nextScene = game->update();
		if(nextScene != game){		// game�Ƃ͈Ⴄ�V�[��(NULL���؂�ւ��̃V�[��)�Ȃ�
			return nextScene;		// ���̃V�[����Ԃ�
		}
	}

	return this;				// �����̃V�[����Ԃ�(�p��)
}

void GameDecorator::display() const
{
	game->display();

	glLoadIdentity();			// ��x���f���r���[������������
	camera->setCamera();		// �J�������Z�b�g

	if(pause_flag){
		glDisable(GL_LIGHTING);
		glColor3d(0.0, 0.0, 0.0);
		glRasterPos3d(-0.4, 0.0, 4.0);

		drawString("PAUSE");
		glEnable(GL_LIGHTING);
	}

	glutSwapBuffers();			// �Ō�ɏo��(SceneManager���ł����ق���������������Ȃ�)
}