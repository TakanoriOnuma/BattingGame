#include "MaterialData.h"

inline void setRGBA(float arr[], float red, float green, float blue, float alpha = 1.0f){
	arr[0] = red;		arr[1] = green;
	arr[2] = blue;		arr[3] = alpha;
}

MaterialData::MaterialData()
{
	setRGBA(ambient, 0.2f, 0.2f, 0.2f);
	setRGBA(diffuse, 0.8f, 0.8f, 0.8f);
	setRGBA(specular, 0.0f, 0.0f, 0.0f);
	shininess = 0.0f;
}

MaterialData MaterialData::createMaterialData(Color color, Material material)
{
	MaterialData matData;

	switch(material){
	case Material::STANDARD:
		switch(color){
		case Color::GREEN:
			setRGBA(matData.ambient, 0.0f, 0.0f, 0.0f);
			setRGBA(matData.diffuse, 0.1f, 0.35f, 0.1f);
			setRGBA(matData.specular, 0.1f, 0.2f, 0.1f);
			matData.shininess = 32.0f;
			break;

		case Color::BLUE:
			setRGBA(matData.ambient, 0.0f, 0.0f, 0.0f);
			setRGBA(matData.diffuse, 0.1f, 0.1f, 0.45f);
			setRGBA(matData.specular, 0.1f, 0.1f, 0.3f);
			matData.shininess = 32.0f;
			break;

		}
		break;

	case Material::PLASTIC:
		switch(color){
		case Color::BLACK:
			setRGBA(matData.ambient, 0.0f, 0.0f, 0.0f);
			setRGBA(matData.diffuse, 0.01f, 0.01f, 0.01f);
			setRGBA(matData.specular, 0.5f, 0.5f, 0.5f);
			matData.shininess = 32.0f;
			break;
		case Color::CYAN:
			setRGBA(matData.ambient, 0.0f, 0.1f, 0.06f);
			setRGBA(matData.diffuse, 0.0f, 0.50980392f, 0.50980392f);
			setRGBA(matData.specular, 0.50196078f, 0.50196078f, 0.50196078f);
			matData.shininess = 32.0f;
			break;
		case Color::GREEN:
			setRGBA(matData.ambient, 0.0f, 0.0f, 0.0f);
			setRGBA(matData.diffuse, 0.1f, 0.35f, 0.1f);
			setRGBA(matData.specular, 0.45f, 0.55f, 0.45f);
			matData.shininess = 32.0f;
			break;
		case Color::RED:
			setRGBA(matData.ambient, 0.0f, 0.0f, 0.0f);
			setRGBA(matData.diffuse, 0.5f, 0.0f, 0.0f);
			setRGBA(matData.specular, 0.7f, 0.6f, 0.6f);
			matData.shininess = 32.0f;
			break;
		case Color::WHITE:
			setRGBA(matData.ambient, 0.0f, 0.0f, 0.0f);
			setRGBA(matData.diffuse, 0.55f, 0.55f, 0.55f);
			setRGBA(matData.specular, 0.7f, 0.7f, 0.7f);
			matData.shininess = 32.0f;
			break;
		case Color::YELLOW:
			setRGBA(matData.ambient, 0.0f, 0.0f, 0.0f);
			setRGBA(matData.diffuse, 0.5f, 0.5f, 0.0f);
			setRGBA(matData.specular, 0.6f, 0.6f, 0.5f);
			matData.shininess = 32.0f;
			break;
		}
		break;

	case Material::RUBBER:
		switch(color){
		case Color::BLACK:
			setRGBA(matData.ambient, 0.02f, 0.02f, 0.02f);
			setRGBA(matData.diffuse, 0.01f, 0.01f, 0.01f);
			setRGBA(matData.specular, 0.4f, 0.4f, 0.4f);
			matData.shininess = 10.0f;
			break;
		case Color::CYAN:
			setRGBA(matData.ambient, 0.0f, 0.05f, 0.05f);
			setRGBA(matData.diffuse, 0.4f, 0.5f, 0.5f);
			setRGBA(matData.specular, 0.04f, 0.7f, 0.7f);
			matData.shininess = 10.0f;
			break;
		case Color::GREEN:
			setRGBA(matData.ambient, 0.0f, 0.05f, 0.0f);
			setRGBA(matData.diffuse, 0.4f, 0.5f, 0.4f);
			setRGBA(matData.specular, 0.04f, 0.7f, 0.04f);
			matData.shininess = 10.0f;
			break;
		case Color::RED:
			setRGBA(matData.ambient, 0.05f, 0.0f, 0.0f);
			setRGBA(matData.diffuse, 0.5f, 0.4f, 0.4f);
			setRGBA(matData.specular, 0.7f, 0.04f, 0.04f);
			matData.shininess = 10.0f;
			break;
		case Color::WHITE:
			setRGBA(matData.ambient, 0.05f, 0.05f, 0.05f);
			setRGBA(matData.diffuse, 0.5f, 0.5f, 0.5f);
			setRGBA(matData.specular, 0.7f, 0.7f, 0.7f);
			matData.shininess = 10.0f;
			break;
		case Color::YELLOW:
			setRGBA(matData.ambient, 0.05f, 0.05f, 0.0f);
			setRGBA(matData.diffuse, 0.5f, 0.5f, 0.4f);
			setRGBA(matData.specular, 0.7f, 0.7f, 0.04f);
			matData.shininess = 10.0f;
			break;
		}
		break;
	}

	return matData;
}

MaterialData MaterialData::createMaterialData(Ore ore)
{
	MaterialData matData;
	switch(ore){
	case Ore::BRASS:
		setRGBA(matData.ambient, 0.329412f, 0.223529f, 0.027451f);
		setRGBA(matData.diffuse, 0.780392f, 0.568627f, 0.113725f);
		setRGBA(matData.specular, 0.992157f, 0.941176f, 0.807843f);
		matData.shininess = 27.89743616f;
		break;
		break;
	case Ore::BRONZE:
		setRGBA(matData.ambient, 0.2125f, 0.1275f, 0.054f);
		setRGBA(matData.diffuse, 0.714f, 0.4284f, 0.18144f);
		setRGBA(matData.specular, 0.393548f, 0.271906f, 0.166721f);
		matData.shininess = 25.6f;
		break;
	case Ore::CHROME:
		setRGBA(matData.ambient, 0.25f, 0.25f, 0.25f);
		setRGBA(matData.diffuse, 0.4f, 0.4f, 0.4f);
		setRGBA(matData.specular, 0.774597f, 0.774597f, 0.774597f);
		matData.shininess = 76.8f;
		break;
	case Ore::GOLD:
		setRGBA(matData.ambient, 0.24725f, 0.1995f, 0.0745f);
		setRGBA(matData.diffuse, 0.75164f, 0.60648f, 0.22648f);
		setRGBA(matData.specular, 0.628281f, 0.555802f, 0.366065f);
		matData.shininess = 51.2f;
		break;
	case Ore::SILVER:
		setRGBA(matData.ambient, 0.19225f, 0.19225f, 0.19225f);
		setRGBA(matData.diffuse, 0.50754f, 0.50754f, 0.50754f);
		setRGBA(matData.specular, 0.508273f, 0.508273f, 0.508273f);
		matData.shininess = 51.2f;
		break;
	case Ore::COPPER:
		setRGBA(matData.ambient, 0.19125f, 0.0735f, 0.0225f);
		setRGBA(matData.diffuse, 0.7038f, 0.27048f, 0.0828f);
		setRGBA(matData.specular, 0.256777f, 0.137622f, 0.086014f);
		matData.shininess = 12.8f;
		break;
	}

	return matData;
}

MaterialData MaterialData::createMaterialData(Jewel jewel)
{
	MaterialData matData;

	switch(jewel){
	case Jewel::EMERALD:
		setRGBA(matData.ambient, 0.0215f, 0.1745f, 0.0215f);
		setRGBA(matData.diffuse, 0.07568f, 0.61424f, 0.07568f);
		setRGBA(matData.specular, 0.0633f, 0.727811f, 0.633f);
		matData.shininess = 76.8f;
		break;
	case Jewel::JADE:
		setRGBA(matData.ambient, 0.135f, 0.2225f, 0.1575f);
		setRGBA(matData.diffuse, 0.54f, 0.89f, 0.63f);
		setRGBA(matData.specular, 0.316228f, 0.316228f, 0.316228f);
		matData.shininess = 12.8f;
		break;
	case Jewel::OBSIDIAN:
		setRGBA(matData.ambient, 0.05375f, 0.05f, 0.06625f);
		setRGBA(matData.diffuse, 0.18275f, 0.17f, 0.22525f);
		setRGBA(matData.specular, 0.332741f, 0.328634f, 0.346435f);
		matData.shininess = 38.4f;
		break;
	case Jewel::PEARL:
		setRGBA(matData.ambient, 0.25f, 0.20725f, 0.20725f);
		setRGBA(matData.diffuse, 1.0f, 0.829f, 0.829f);
		setRGBA(matData.specular, 0.296648f, 0.296648f, 0.296648f);
		matData.shininess = 10.24f;
		break;
	case Jewel::RUBY:
		setRGBA(matData.ambient, 0.1745f, 0.01175f, 0.01175f);
		setRGBA(matData.diffuse, 0.61424f, 0.04136f, 0.04136f);
		setRGBA(matData.specular, 0.727811f, 0.626959f, 0.626959f);
		matData.shininess = 76.8f;
		break;
	case Jewel::TURQUOISE:
		setRGBA(matData.ambient, 0.1f, 0.18725f, 0.1745f);
		setRGBA(matData.diffuse, 0.396f, 0.74151f, 0.69102f);
		setRGBA(matData.specular, 0.297254f, 0.30829f, 0.306678f);
		matData.shininess = 12.8f;
		break;
	}
	return matData;

}