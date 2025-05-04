#include "Scene10.h"
#include <iostream>

#include <glm/gtc/type_ptr.hpp>

void Scene10::init()
{
	Scene::init();

	// allocate memory and load resources
	// Lights

	//Esta es la luz que se moverrá con el caza
	mFighterLight = new SpotLight(getSpotLightID());
	gLights.push_back( { mFighterLight, ON } );

	//// XY light fixed
	mPosLightXY = new PosLightXY(getPosLightID());
	gLights.push_back( { mPosLightXY, ON } );

	//// YZ light fixed
	mSpotLightYZ = new SpotLightYZ(getSpotLightID());
	gLights.push_back({ mSpotLightYZ, ON });

	// Textures

	// Graphics objects (entities) of the scene

	
	gObjects.push_back(new Sphere(150, 20, 30, glm::vec4(1, 0.91, 0, 1)));

	orbInventedNode = new CompoundEntity();
	rotInventedNode = new CompoundEntity();

	lightReference = new CompoundEntity(); // to move light with fighter

	fighter = new TieFighter();
	fighter->setWPos(glm::vec3(0, 220, 0));
	lightReference->setWPos(fighter->getWPos() - glm::vec3(0, 20, 0));
	//lightReference->setWPos(glm::vec3(0, 200, 0));
	mFighterLight->setPosition(lightReference->getWPos());
	mFighterLight->setDirection(glm::vec3(0) - mFighterLight->getPosition());


	rotInventedNode->addEntity(fighter);
	rotInventedNode->addEntity(lightReference);

	orbInventedNode->addEntity(rotInventedNode);

	gObjects.push_back(orbInventedNode);

	// Fighter light position and direction to change with it

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

	// Set the position of the light combining all matrices up to world:
	glm::vec3 pos = glm::vec3(
		orbInventedNode->modelMat() *
		rotInventedNode->modelMat() *
		lightReference->modelMat() *
		glm::vec4(0, 0, 0, 1)); // modelMat()[3] is the postion xyz

	glm::vec3 dir = glm::normalize(glm::vec3(
		orbInventedNode->modelMat() *
		rotInventedNode->modelMat() *
		lightReference->modelMat() *
		glm::vec4(0, 0, -1, 0)));  // local forward to world direction

	mFighterLight->setPosition(pos);
	mFighterLight->setDirection(dir);
}


