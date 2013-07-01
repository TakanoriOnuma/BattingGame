#ifndef ___Class_SceneManager
#define ___Class_SceneManager

#include "IScene.h"
#include "IAnimation.h"

class SceneManager : IAnimation{
	IScene* scene;

	SceneManager();
	SceneManager(const SceneManager&);

	static void _update();
	static void _display();

public:
	~SceneManager();
	static SceneManager& getInstance();
	void setScene(IScene* scene);		// �Z�b�g�ł���͍̂ŏ���1�񂾂�

	void update() override;
	void display() const;
};


#endif