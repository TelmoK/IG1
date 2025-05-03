#include "Scene7.h"


void Scene7::init()
{
	setGL(); // OpenGL settings

	// allocate memory and load resources
	// Lights
	// Textures

	// Graphics objects (entities) of the scene
	gObjects.push_back(new RGBAxes(400.0));
	gObjects.push_back(new Toros(200, 50, 40, 40));

}

void Scene7::update()
{
	for (auto* o : gObjects)
		o->update();
}