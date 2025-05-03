#include "Scene4.h"
#include <glm/gtc/matrix_transform.hpp>

void Scene4::init()
{
	Scene::init();

	// allocate memory and load resources
	// Lights
	// Textures

	// Graphics objects (entities) of the scene
	gObjects.push_back(new RGBCube(100.0));
}