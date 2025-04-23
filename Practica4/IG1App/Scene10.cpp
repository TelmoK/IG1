#include "Scene10.h"

void Scene10::init()
{
	setGL(); // OpenGL settings

	// allocate memory and load resources
	// Lights
	// Textures

	// Graphics objects (entities) of the scene
	gObjects.push_back(new RGBAxes(400.0));

	gObjects.push_back(new Sphere(300.0, 20, 30, glm::dvec4(1, 0.9, 0, 1)));

	TieFighter* fighter = new TieFighter();
	fighter->setWPos(glm::vec3(0, 340,0));
	gObjects.push_back(fighter);

}