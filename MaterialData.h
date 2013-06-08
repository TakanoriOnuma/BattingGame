#ifndef ___Struct_MaterialData
#define ___Struct_MaterialData

// --- �F�̗� --- //
enum class Color{
	RED,			// ��
	GREEN,			// ��
	BLUE,			// ��
	YELLOW,			// ���F
	BLACK,			// ��
	WHITE,			// ��
	CYAN,			// �V�A��
};

// --- �F�ɑ΂����ނ̗� --- //
enum class Material{
	STANDARD,		// ���ʂ̍ގ�(�ގ��w��Ȃ�)
	PLASTIC,		// �v���X�e�B�b�N
	RUBBER,			// �S��
};

// --- �z�΂̗� --- //
enum class Ore{
	GOLD,			// ��
	SILVER,			// ��
	COPPER,			// ��
	BRASS,			// �^�J
	BRONZE,			// ��
	CHROME,			// �N����
};

// --- ��΂̗� --- //
enum class Jewel{
	EMERALD,		// �G�������h
	JADE,			// �Ő�
	OBSIDIAN,		// ���j��
	PEARL,			// �^��
	RUBY,			// ���r�[
	TURQUOISE,		// �g���R��
};

struct MaterialData{
	// --- material�̃f�[�^ --- //
	float ambient[4];
	float diffuse[4];
	float specular[4];
	float shininess;

	MaterialData();
	static MaterialData createMaterialData(Color color, Material material = Material::STANDARD);
	static MaterialData createMaterialData(Ore ore);
	static MaterialData createMaterialData(Jewel jewel);
};


#endif