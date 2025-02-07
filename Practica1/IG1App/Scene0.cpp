#include "Scene0.h"

void Scene0::init()
{
	setGL(); // OpenGL settings

	// allocate memory and load resources
	// Lights
	// Textures

	// Graphics objects (entities) of the scene
	gObjects.push_back(new RGBAxes(400.0));
	gObjects.push_back(new RegularPolygon(4, 100));
	gObjects.push_back(new SingleColorEntity());
}