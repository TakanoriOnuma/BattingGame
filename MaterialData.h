#ifndef ___Struct_MaterialData
#define ___Struct_MaterialData

// --- 色の列挙 --- //
enum class Color{
	RED,			// 赤
	GREEN,			// 緑
	BLUE,			// 青
	YELLOW,			// 黄色
	BLACK,			// 黒
	WHITE,			// 白
	CYAN,			// シアン
};

// --- 色に対する種類の列挙 --- //
enum class Material{
	STANDARD,		// 普通の材質(材質指定なし)
	PLASTIC,		// プラスティック
	RUBBER,			// ゴム
};

// --- 鉱石の列挙 --- //
enum class Ore{
	GOLD,			// 金
	SILVER,			// 銀
	COPPER,			// 銅
	BRASS,			// 真鍮
	BRONZE,			// 青銅
	CHROME,			// クロム
};

// --- 宝石の列挙 --- //
enum class Jewel{
	EMERALD,		// エメラルド
	JADE,			// 翡翠
	OBSIDIAN,		// 黒曜石
	PEARL,			// 真珠
	RUBY,			// ルビー
	TURQUOISE,		// トルコ石
};

struct MaterialData{
	// --- materialのデータ --- //
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