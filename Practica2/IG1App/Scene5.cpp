#include "Scene5.h"
#include <glm/gtc/matrix_transform.hpp>
#include <memory>

Scene5::~Scene5()
{
	delete txBox;
	delete txBoxInt;
}

void Scene5::init()
{
	setGL(); // OpenGL settings

	// allocate memory and load resources
	// Lights
	// Textures

	// Graphics objects (entities) of the scene
	gObjects.push_back(new RGBAxes(400.0));
	
	//Texture* tx = new Texture();
	//tx->load("../assets/images/baldosaC.png");
	//gObjects.push_back(new Ground(tx, false, 100.0, 100.0));

	txBox = new Texture();
	txBox->load("../assets/images/container.jpg");

	txBoxInt = new Texture();
	txBoxInt->load("../assets/images/papelE.png");

	gObjects.push_back(new BoxOutline(txBox, txBoxInt, false, 80));
}