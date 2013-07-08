#ifndef ___Class_KeyboardManager
#define ___Class_KeyboardManager

#include <vector>
#include <bitset>

#include "KeyboardListener.h"

enum class SpecialKey{
	LEFT,		// ���L�[
	UP,			// ��L�[
	RIGHT,		// �E�L�[
	DOWN,		// ���L�[

	SIZE,		// SpecialKey�̎�ނ̐�
};

class KeyboardManager{
	friend void _keyboard(unsigned char key, int x, int y);
	friend void _keyboardUp(unsigned char key, int x, int y);
	friend void _specialKeyboard(int key, int x, int y);
	friend void _specialKeyboardUp(int key, int x, int y);

private:
	std::bitset<256> char_key;
	std::bitset<static_cast<size_t>(SpecialKey::SIZE)> special_key;

	// --- �O���[�o���֐��̃f���Q�[�g�֐� --- //
	void (*char_key_handlar)(unsigned char key, int x, int y);
	void (*char_key_up_handlar)(unsigned char key, int x, int y);
	void (*special_key_handlar)(int key, int x, int y);
	void (*special_key_up_handlar)(int key, int x, int y);

	// --- �L�[�{�[�h���X�i�[ --- //
	std::vector<KeyboardListener*> listeners;


	KeyboardManager();
	KeyboardManager(const KeyboardManager&);
public:
	~KeyboardManager();

	static KeyboardManager& getInstance();

	void useCharKeyboard();
	void useSpecialKeyboard();

	bool isPushCharKey(unsigned char key) const{
		return char_key[key];
	}
	bool isPushSpecialKey(SpecialKey key) const{
		return special_key[static_cast<size_t>(key)];
	}

	// --- �O���[�o���֐��̃f���Q�[�g�֐����Z�b�g --- //
	void setKeyboardHandlar(void (*char_key_handlar)(unsigned char key, int x, int y)){
		this->char_key_handlar = char_key_handlar;
	}
	void setKeyboardUpHandlar(void (*char_key_up_handlar)(unsigned char key, int x, int y)){
		this->char_key_up_handlar = char_key_up_handlar;
	}
	void setSpecialKeyboarHandlar(void (*special_key_handlar)(int key, int x, int y)){
		this->special_key_handlar = special_key_handlar;
	}
	void setSpecialKeyboardUpHandlar(void (*special_key_up_handlar)(int key, int x, int y)){
		this->special_key_up_handlar = special_key_up_handlar;
	}

	void addListener(KeyboardListener* listener);
	void removeListener(KeyboardListener* listener);
};


#endif