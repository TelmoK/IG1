#include "Scene6.h"

void Scene6::init()
{
	setGL(); // OpenGL settings

	// allocate memory and load resources
	// Lights
	// Textures

	// Graphics objects (entities) of the scene
	gObjects.push_back(new RGBAxes(400.0));

	Texture* tx = new Texture();
	tx->load("../assets/images/baldosaP.png");

	gObjects.push_back(new Star3D(tx, false, 300, 8, 100));
}

void Scene6::update()
{
	for (auto* o : gObjects)
		o->update();
}

