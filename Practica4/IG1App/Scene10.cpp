#include "Scene10.h"

#include <glm/gtc/type_ptr.hpp>

void Scene10::init()
{
	setGL(); // OpenGL settings

	// allocate memory and load resources
	// Lights
	// Textures

	// Graphics objects (entities) of the scene
	gObjects.push_back(new RGBAxes(400.0));

	gObjects.push_back(new Sphere(300.0, 20, 30, glm::dvec4(1, 0.91, 0, 1)));

	orbInventedNode = new CompoundEntity();

	TieFighter* fighter = new TieFighter();

	orbInventedNode->addEntity(fighter);

	fighter->setWPos(glm::vec3(0, 340,0));
	gObjects.push_back(orbInventedNode);

}

void Scene10::rotate()
{
	
}

void Scene10::orbit()
{
	orbInventedNode->setModelMat(glm::rotate(orbInventedNode->modelMat(), glm::radians(3.0f), glm::vec3(0, 0, 1)));
}
