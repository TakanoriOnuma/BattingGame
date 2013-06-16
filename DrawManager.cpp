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

// 関数に内部変数を持たせてシングルトンを実装する
DrawManager& DrawManager::getDrawManager()
{
	static DrawManager drawManager;
	return drawManager;
}

void DrawManager::setDrawObject(DrawObject* drawObject)
{
	// 既に登録されているか調べる
	list<DrawObject*>::iterator pos = find(drawList.begin(), drawList.end(), drawObject);

	if(pos == drawList.end()){				// 登録されていなければ
		drawList.push_back(drawObject);		// 登録する
	}
}

void DrawManager::removeDrawObject(DrawObject* drawObject)
{
	drawList.remove(drawObject);		// リストから消去する
}

void DrawManager::draw() const
{
	list<DrawObject*>::const_iterator it;
	for(it = drawList.begin(); it != drawList.end(); ++it){
		(*it)->draw(true, true);
	}
}