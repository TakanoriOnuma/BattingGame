#ifndef ___Class_KeyboardListener
#define ___Class_KeyboardListener


class KeyboardListener{

public:
	virtual ~KeyboardListener(){ }
	virtual void keyboard(unsigned char key, int x, int y) = 0;
	virtual void keyboardUp(unsigned char key, int x, int y) = 0;
	virtual void specialKeyboard(int key, int x, int y) = 0;
	virtual void specialKeyboardUp(int key, int x, int y) = 0;
};

#endif