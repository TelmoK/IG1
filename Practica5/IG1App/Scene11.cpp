#include "Scene11.h"

void Scene11::init()
{
	setGL(); // OpenGL settings

	// allocate memory and load resources
	// Lights
	gLights.push_back(new DirLight(1));
	// Textures

	// Graphics objects (entities) of the scene
	gObjects.push_back(new RGBAxes(400.0));

	gObjects.push_back(new Sphere(300.0, 20, 30, glm::dvec4(1, 0.91, 0, 1)));
}
