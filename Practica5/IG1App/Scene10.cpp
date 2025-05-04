#include "Scene10.h"

#include <glm/gtc/type_ptr.hpp>

void Scene10::init()
{
	Scene::init();

	// allocate memory and load resources
	// Lights

	// Esta es la luz que se moverrá con el caza
	mFighterLight = new SpotLight();
	gLights.push_back( { mFighterLight, ON } );

	// XY light fixed
	mPosLightXY = new PosLightXY();
	gLights.push_back( { mPosLightXY, ON } );

	// YZ light fixed
	mSpotLightYZ = new SpotLightYZ();
	gLights.push_back({ mSpotLightYZ, ON });

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

	// Fighter light position and direction to change with it
	mFighterLight->setPosition(glm::vec3(0, 170, 0));
	mFighterLight->setDirection(glm::vec3(0) - glm::vec3(0, 220, 0));

}

void Scene10::setColor()
{
	glClearColor(.0, .0, .0, .0);
}

void Scene10::toggleLightWithKey_T()
{
	toggleLight(mPosLightXY);
}

void Scene10::toggleLightWithKey_Y()
{
	toggleLight(mSpotLightYZ);
}

void Scene10::toggleLightWithKey_H()
{
	toggleLight(mFighterLight);
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

	//newFighterLight_pos = 

	//mFighterLight->setDirection(glm::vec3(0) - newFighterLight_pos);
}


