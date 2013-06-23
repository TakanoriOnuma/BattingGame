#ifndef ___Class_MouseManager
#define ___Class_MouseManager

#include <bitset>
#include <vector>

#include "MyPoint.h"
#include "MouseListener.h"

enum class MouseClick{
	LEFT,		// ���N���b�N
	MIDDLE,		// ���N���b�N
	RIGHT,		// �E�N���b�N

	SIZE,		// MouseClick�̎�ނ̐�
};

class MouseManager{
	friend void _passive(int x, int y);
	friend void _motion(int x, int y);
	friend void _mouse(int button, int state, int x, int y);
	friend void _wheel(int wheel_number, int direction, int x, int y);

private:
	Point2i pt;		// �}�E�X���W
	std::bitset<static_cast<size_t>(MouseClick::SIZE)> state;	// �L�[���͂̏��

	// --- �N���[�o���֐��̃f���Q�[�g�֐� --- //
	void (*passive_handlar)(int x, int y);
	void (*motion_handlar)(int x, int y);
	void (*mouse_handlar)(int button, int state, int x, int y);
	void (*wheel_handlar)(int wheel_number, int direction, int x, int y);

	// --- �N���X�̃��X�i�[ --- //
	std::vector<MouseListener*> listeners;

	MouseManager();
	MouseManager(const MouseManager&);
public:
	static MouseManager& getMouseManager();

	void useMouse();

	const Point2i& getMousePoint() const{
		return pt;
	}
	bool isClick(MouseClick mouse) const{
		return state[static_cast<size_t>(mouse)];
	}
	const std::bitset<static_cast<size_t>(MouseClick::SIZE)>& getMouseState() const{
		return state;
	}

	// --- �O���[�o���֐��̃f���Q�[�g�֐����Z�b�g --- //
	void setPassiveHandlar(void (*passive_handlar)(int x, int y)){
		this->passive_handlar = passive_handlar;
	}
	void setMotionHandlar(void (*motion_handlar)(int x, int y)){
		this->motion_handlar = motion_handlar;
	}
	void setMouseHandlar(void (*mouse_handlar)(int button, int state, int x, int y)){
		this->mouse_handlar = mouse_handlar;
	}
	void setWheelHandlar(void (*wheel_handlar)(int wheel_number, int direction, int x, int y)){
		this->wheel_handlar = wheel_handlar;
	}

	// --- ���X�i�[�̓o�^�Ɖ��� --- //
	void addListener(MouseListener* listener);
	void removeListener(MouseListener* listener);
};


#endif