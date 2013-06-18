#ifndef ___Class_ExecuteScene
#define ___Class_ExecuteScene

#include "IScene.h"
#include "IAnimation.h"

class ExecuteScene : IAnimation{
	IScene* scene;

	ExecuteScene();
	ExecuteScene(const ExecuteScene&);

	static void _update();
	static void _display();

public:
	~ExecuteScene();
	static ExecuteScene& getExecuteScene();
	void setScene(IScene* scene);		// セットできるのは最初の1回だけ

	void update() override;
	void display() const;
};


#endif