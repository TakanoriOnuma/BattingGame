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
	void setScene(IScene* scene);		// ƒZƒbƒg‚Å‚«‚é‚Ì‚ÍÅ‰‚Ì1‰ñ‚¾‚¯

	void update() override;
	void display() const;
};


#endif