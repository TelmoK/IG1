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

	inventedNode = new CompoundEntity();

	TieFighter* fighter = new TieFighter();

	inventedNode->addEntity(fighter);

	fighter->setWPos(glm::vec3(0, 340,0));
	gObjects.push_back(inventedNode);

}

void Scene10::rotate()
{
	
}

void Scene10::orbit()
{
	inventedNode->setModelMat(glm::rotate(inventedNode->modelMat(), glm::radians(3.0f), glm::vec3(0, 0, 1)));
}
