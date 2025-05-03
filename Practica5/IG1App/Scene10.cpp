#include "Scene10.h"

#include <glm/gtc/type_ptr.hpp>

void Scene10::init()
{
	Scene::init();

	// allocate memory and load resources
	// Lights
	SpotLight* spotlight = new SpotLight();
	gLights.push_back(spotlight);
	// Textures

	// Graphics objects (entities) of the scene

	gObjects.push_back(new Sphere(150, 20, 30, glm::vec4(1, 0.91, 0, 1)));

	orbInventedNode = new CompoundEntity();
	rotInventedNode = new CompoundEntity();

	TieFighter* fighter = new TieFighter();

	rotInventedNode->addEntity(fighter);
	orbInventedNode->addEntity(rotInventedNode);

	fighter->setWPos(glm::vec3(0, 220, 0));
	gObjects.push_back(orbInventedNode);

	spotlight->setPosition(glm::vec3(0, 170, 0));
	spotlight->setDirection(glm::vec3(0) - glm::vec3(0, 220, 0));

}

void Scene10::setColor()
{
	glClearColor(.0, .0, .0, .0);
}

void Scene10::rotate()
{
	// Rotamos la nave sobre s� misma rotando respecto a su vector up (eje Y)
	rotInventedNode->setModelMat(glm::rotate(rotInventedNode->modelMat(), glm::radians(-3.0f), glm::vec3(0, 1, 0)));
}

void Scene10::orbit()
{
	// Por defecto se orbita sobre el eje Z pero hay que rotar este eje cunado rotamos la nave
	// para que se mantenga la direcci�n de rotaci�n correcta, por lo que aplicamos la misma 
	// matriz de modelado rotada del ficticio de rotaci�n sobre un vector en la direcci�n del eje
	// Z (porque es perpendicular a la direcci�n a la que mira la nave inicialmente, que es el eje X)
	glm::vec3 rotatedOrbitAxis = glm::vec3(rotInventedNode->modelMat() * glm::vec4(0, 0, 1, 0));

	orbInventedNode->setModelMat(glm::rotate(orbInventedNode->modelMat(), glm::radians(-3.0f), rotatedOrbitAxis));
}
