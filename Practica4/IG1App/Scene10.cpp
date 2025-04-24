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
	rotInventedNode = new CompoundEntity();

	TieFighter* fighter = new TieFighter();

	rotInventedNode->addEntity(fighter);
	orbInventedNode->addEntity(rotInventedNode);

	fighter->setWPos(glm::vec3(0, 340,0));
	gObjects.push_back(orbInventedNode);

}

void Scene10::rotate()
{
	// Rotamos la nave sobre sí misma rotando respecto a su vector up (eje Y)
	rotInventedNode->setModelMat(glm::rotate(rotInventedNode->modelMat(), glm::radians(3.0f), glm::vec3(0, 1, 0)));
}

void Scene10::orbit()
{
	// Por defecto se orbita sobre el eje Z pero hay que rotar este eje cunado rotamos la nave
	// para que se mantenga la dirección de rotación correcta, por lo que aplicamos la misma 
	// matriz de modelado rotada del ficticio de rotación sobre un vector en la dirección del eje
	// Z (porque es perpendicular a la dirección a la que mira la nave inicialmente, que es el eje X)
	glm::vec3 rotatedOrbitAxis = glm::vec3(rotInventedNode->modelMat() * glm::vec4(0, 0, 1, 0));

	orbInventedNode->setModelMat(glm::rotate(orbInventedNode->modelMat(), glm::radians(3.0f), rotatedOrbitAxis));
}
