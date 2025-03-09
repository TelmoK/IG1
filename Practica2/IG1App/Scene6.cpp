#include "Scene6.h"


void Scene6::init()
{
	setGL(); // OpenGL settings

	// allocate memory and load resources
	// Lights
	// Textures
	Texture* txGlass = new Texture();
	txGlass->load("../assets/images/windowV.jpg", 122);
	gTextures.push_back(txGlass);

	// Objeto de textura de la foto a ser sacada
	Texture* foto = new Texture();
	gTextures.push_back(foto);

	// Graphics objects (entities) of the scene
	gObjects.push_back(new RGBAxes(400.0));
	gObjects.push_back(new GlassParapet(txGlass, false, 200));
	gObjects.push_back(new Photo(foto, false, 200, 200));


}

void Scene6::update()
{
	for (auto* o : gObjects)
		o->update();
}

