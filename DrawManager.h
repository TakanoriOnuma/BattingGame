#ifndef ___Class_DrawManager
#define ___Class_DrawManager

#include <list>

class DrawObject;

class DrawManager{
	std::list<DrawObject*> drawList;	// Drawer‚ğƒŠƒXƒg‚Å•Û

	DrawManager();
	DrawManager(const DrawManager&);

public:
	static DrawManager& getDrawManager();
	~DrawManager();

	void setDrawObject(DrawObject* drawObject);
	void removeDrawObject(DrawObject* drawObject);
	void draw() const;
};


#endif