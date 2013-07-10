#include "OpenGL.h"
#include "KeyboardManager.h"

#include <iostream>
#include <algorithm>

using namespace std;

/* friend 関数の定義 */
void _keyboard(unsigned char key, int x, int y)
{
	KeyboardManager& keyManager = KeyboardManager::getInstance();

	if(keyManager.char_key_handlar != NULL){
		keyManager.char_key_handlar(key, x, y);
	}

	for each (KeyboardListener* listener in keyManager.listeners)
	{
		listener->keyboard(key, x, y);
	}

	keyManager.char_key.set(key);
}

void _keyboardUp(unsigned char key, int x, int y)
{
	KeyboardManager& keyManager = KeyboardManager::getInstance();

	if(keyManager.char_key_up_handlar != NULL){
		keyManager.char_key_up_handlar(key, x, y);
	}

	for each (KeyboardListener* listener in keyManager.listeners)
	{
		listener->keyboardUp(key, x, y);
	}

	keyManager.char_key.reset(key);
}

void _specialKeyboard(int key, int x, int y)
{
	KeyboardManager& keyManager = KeyboardManager::getInstance();

	if(keyManager.special_key_handlar != NULL){
		keyManager.special_key_handlar(key, x, y);
	}

	for each (KeyboardListener* listener in keyManager.listeners)
	{
		listener->specialKeyboard(key, x, y);
	}

	switch(key){
	case GLUT_KEY_LEFT:
		keyManager.special_key.set(static_cast<size_t>(SpecialKey::LEFT));
		break;
	case GLUT_KEY_UP:
		keyManager.special_key.set(static_cast<size_t>(SpecialKey::UP));
		break;
	case GLUT_KEY_RIGHT:
		keyManager.special_key.set(static_cast<size_t>(SpecialKey::RIGHT));
		break;
	case GLUT_KEY_DOWN:
		keyManager.special_key.set(static_cast<size_t>(SpecialKey::DOWN));
		break;
	}
}

void _specialKeyboardUp(int key, int x, int y)
{
	KeyboardManager& keyManager = KeyboardManager::getInstance();

	if(keyManager.special_key_up_handlar != NULL){
		keyManager.special_key_up_handlar(key, x, y);
	}

	for each (KeyboardListener* listener in keyManager.listeners)
	{
		listener->keyboardUp(key, x, y);
	}

	switch(key){
	case GLUT_KEY_LEFT:
		keyManager.special_key.reset(static_cast<size_t>(SpecialKey::LEFT));
		break;
	case GLUT_KEY_UP:
		keyManager.special_key.reset(static_cast<size_t>(SpecialKey::UP));
		break;
	case GLUT_KEY_RIGHT:
		keyManager.special_key.reset(static_cast<size_t>(SpecialKey::RIGHT));
		break;
	case GLUT_KEY_DOWN:
		keyManager.special_key.reset(static_cast<size_t>(SpecialKey::DOWN));
		break;
	}
}


// ===== KeyboardManagerメンバ関数の定義 ===== //
KeyboardManager::KeyboardManager()
	: char_key_handlar(NULL), char_key_up_handlar(NULL),
	special_key_handlar(NULL), special_key_up_handlar(NULL)
{
	std::cout << "create KeyboadManager" << std::endl;
}

// 関数に内部変数を持たせてシングルトンを実装する
KeyboardManager& KeyboardManager::getInstance()
{
	static KeyboardManager keyboardManager;
	return keyboardManager;
}

KeyboardManager::~KeyboardManager()
{
	std::cout << "delete KeyboardManager" << std::endl;
}


void KeyboardManager::useCharKeyboard()
{
	glutKeyboardFunc(_keyboard);
	glutKeyboardUpFunc(_keyboardUp);
}

void KeyboardManager::useSpecialKeyboard()
{
	glutSpecialFunc(_specialKeyboard);
	glutSpecialUpFunc(_specialKeyboardUp);
}

void KeyboardManager::addListener(KeyboardListener* listener)
{
	vector<KeyboardListener*>::iterator pos =
		find(listeners.begin(), listeners.end(), listener);

	// 登録されなかったら
	if(pos == listeners.end()){
		listeners.push_back(listener);
	}
}

void KeyboardManager::removeListener(KeyboardListener* listener)
{
	vector<KeyboardListener*>::iterator end_it =
		remove(listeners.begin(), listeners.end(), listener);

	listeners.erase(end_it, listeners.end());
}