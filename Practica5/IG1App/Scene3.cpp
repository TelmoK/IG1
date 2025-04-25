#include "Scene3.h"
#include <glm/gtc/matrix_transform.hpp>

void Scene3::init()
{
	setGL(); // OpenGL settings

	// allocate memory and load resources
	// Lights
	// Textures

	// Graphics objects (entities) of the scene
	gObjects.push_back(new RGBAxes(400.0));
	gObjects.push_back(new Cube(100.0));

}