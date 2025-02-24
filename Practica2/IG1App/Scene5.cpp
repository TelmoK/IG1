#include "Scene5.h"
#include <glm/gtc/matrix_transform.hpp>

void Scene5::init()
{
	setGL(); // OpenGL settings

	// allocate memory and load resources
	// Lights
	// Textures

	// Graphics objects (entities) of the scene
	gObjects.push_back(new RGBAxes(400.0));
	/*
	Texture* tx = new Texture();
	tx->load("../assets/images/baldosaC.png");
	gObjects.push_back(new Ground(tx, false, 100.0, 100.0));*/

	Texture* txBox = new Texture();
	txBox->load("../assets/images/container.jpg");
	gObjects.push_back(new BoxOutline(txBox, false, 80));
}