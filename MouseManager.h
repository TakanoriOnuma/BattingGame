#ifndef ___Class_MouseManager
#define ___Class_MouseManager

#include <bitset>
#include <vector>

#include "MyPoint.h"
#include "MouseListener.h"

enum class MouseClick{
	LEFT,		// 左クリック
	MIDDLE,		// 中クリック
	RIGHT,		// 右クリック

	SIZE,		// MouseClickの種類の数
};

class MouseManager{
	friend void _passive(int x, int y);
	friend void _motion(int x, int y);
	friend void _mouse(int button, int state, int x, int y);
	friend void _wheel(int wheel_number, int direction, int x, int y);

private:
	Point2i pt;		// マウス座標
	std::bitset<static_cast<size_t>(MouseClick::SIZE)> state;	// キー入力の状態

	// --- クローバル関数のデリゲート関数 --- //
	void (*passive_handlar)(int x, int y);
	void (*motion_handlar)(int x, int y);
	void (*mouse_handlar)(int button, int state, int x, int y);
	void (*wheel_handlar)(int wheel_number, int direction, int x, int y);

	// --- クラスのリスナー --- //
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

	// --- グローバル関数のデリゲート関数をセット --- //
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

	// --- リスナーの登録と解除 --- //
	void addListener(MouseListener* listener);
	void removeListener(MouseListener* listener);
};


#endif