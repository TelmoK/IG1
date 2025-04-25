#include "Scene5.h"


void Scene5::init()
{
	setGL(); // OpenGL settings

	// allocate memory and load resources
	// Lights
	// Textures
	Texture* txBox = new Texture();
	Texture* txBoxInt = new Texture();
	txBox->load("../assets/images/container.jpg");
	gTextures.push_back(txBox);
	txBoxInt->load("../assets/images/papelE.png");
	gTextures.push_back(txBoxInt);

	// Graphics objects (entities) of the scene
	gObjects.push_back(new RGBAxes(400.0));
	gObjects.push_back(new BoxOutline(txBox, txBoxInt, false, 200));
}