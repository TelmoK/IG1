#include "Scene0.h"
#include <glm/gtc/matrix_transform.hpp>

void Scene0::init()
{
	Scene::init();

	// allocate memory and load resources
	// Lights
	// Textures

	// Graphics objects (entities) of the scene
	gObjects.push_back(new RegularPolygon(3, 100, glm::vec4(0, 255, 255, 1)));
	gObjects.push_back(new RegularPolygon(100, 100, glm::vec4(255, 0, 255, 1)));
	
	RGBTriangle* rgbTriangle = new RGBTriangle(20);

	rgbTriangle->setWPos({100,0,0});

	gObjects.push_back(rgbTriangle);
}

void Scene0::update()
{
	for (auto* o : gObjects)
		o->update();
}