#include "Scene3.h"
#include <glm/gtc/matrix_transform.hpp>

void Scene3::init()
{
	Scene::init();

	// allocate memory and load resources
	// Lights
	// Textures

	// Graphics objects (entities) of the scene
	gObjects.push_back(new Cube(100.0, glm::vec4(1, 1, 0, 1)));

}