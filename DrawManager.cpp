#include "OpenGL.h"
#include "DrawManager.h"
#include "DrawObject.h"

using namespace std;


DrawManager::DrawManager() : drawList()
{
}

DrawManager::~DrawManager()
{
	list<DrawObject*>::iterator it;
	for(it = drawList.begin(); it != drawList.end(); ++it){
		delete *it;
	}
}

// ŠÖ”‚É“à•”•Ï”‚ğ‚½‚¹‚ÄƒVƒ“ƒOƒ‹ƒgƒ“‚ğÀ‘•‚·‚é
DrawManager& DrawManager::getDrawManager()
{
	static DrawManager drawManager;
	return drawManager;
}

void DrawManager::setDrawObject(DrawObject* drawObject)
{
	// Šù‚É“o˜^‚³‚ê‚Ä‚¢‚é‚©’²‚×‚é
	list<DrawObject*>::iterator pos = find(drawList.begin(), drawList.end(), drawObject);

	if(pos == drawList.end()){				// “o˜^‚³‚ê‚Ä‚¢‚È‚¯‚ê‚Î
		drawList.push_back(drawObject);		// “o˜^‚·‚é
	}
}

void DrawManager::removeDrawObject(DrawObject* drawObject)
{
	// “o˜^‚³‚ê‚Ä‚¢‚é‚©’²‚×‚é
	list<DrawObject*>::iterator pos = find(drawList.begin(), drawList.end(), drawObject);

	if(pos != drawList.end()){				// “o˜^‚µ‚Ä‚ ‚ê‚Î
		delete *pos;						// ‚»‚ÌêŠ‚Ìƒ|ƒCƒ“ƒ^‚ğdelete‚·‚é
		drawList.remove(drawObject);		// ƒŠƒXƒg‚©‚çÁ‹‚·‚é
	}

}

void DrawManager::draw() const
{
	list<DrawObject*>::const_iterator it;
	for(it = drawList.begin(); it != drawList.end(); ++it){
		(*it)->draw(true, true);
	}
}