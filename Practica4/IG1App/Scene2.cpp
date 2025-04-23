#include "Scene2.h"


void Scene2::init()
{
	setGL(); // OpenGL settings

	// allocate memory and load resources
	// Lights
	// Textures

	// Graphics objects (entities) of the scene
	gObjects.push_back(new RGBAxes(400.0));
	gObjects.push_back(new RGBTriangle(20));
	gObjects.push_back(new RGBRectangle(400, 200));
	gObjects.push_back(new RegularPolygon(100, 200, glm::vec4(1)));
}

void Scene2::update()
{
	for (auto* o : gObjects)
		o->update();
}