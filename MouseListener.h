#ifndef ___Class_MouseListener
#define ___Class_MouseListener


class MouseListener{

public:
	~MouseListener(){ }

	virtual void passive(int x, int y) = 0;
	virtual void motion(int x, int y) = 0;
	virtual void mouse(int button, int state, int x, int y) = 0;
	virtual void wheel(int wheel_number, int direction, int x, int y) = 0;
};

#endif