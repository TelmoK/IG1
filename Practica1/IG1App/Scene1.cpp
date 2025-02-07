#include "Scene1.h"

void Scene1::init()
{
	setGL(); // OpenGL settings

	// allocate memory and load resources
	// Lights
	// Textures

	// Graphics objects (entities) of the scene
	//gObjects.push_back(new RGBAxes(400.0));
	gObjects.push_back(new RGBTriangle(100));
	//gObjects.push_back(new RegularPolygon(3, 100, glm::dvec4(0, 255, 255, 1)));
}