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

// �֐��ɓ����ϐ����������ăV���O���g������������
DrawManager& DrawManager::getDrawManager()
{
	static DrawManager drawManager;
	return drawManager;
}

void DrawManager::setDrawObject(DrawObject* drawObject)
{
	// ���ɓo�^����Ă��邩���ׂ�
	list<DrawObject*>::iterator pos = find(drawList.begin(), drawList.end(), drawObject);

	if(pos == drawList.end()){				// �o�^����Ă��Ȃ����
		drawList.push_back(drawObject);		// �o�^����
	}
}

void DrawManager::removeDrawObject(DrawObject* drawObject)
{
	// �o�^����Ă��邩���ׂ�
	list<DrawObject*>::iterator pos = find(drawList.begin(), drawList.end(), drawObject);

	if(pos != drawList.end()){				// �o�^���Ă����
		delete *pos;						// ���̏ꏊ�̃|�C���^��delete����
		drawList.remove(drawObject);		// ���X�g�����������
	}

}

void DrawManager::draw() const
{
	list<DrawObject*>::const_iterator it;
	for(it = drawList.begin(); it != drawList.end(); ++it){
		(*it)->draw(true, true);
	}
}