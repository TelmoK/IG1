#include "Scene6.h"
#include "IG1App.h"


void Scene6::init()
{
	setGL(); // OpenGL settings

	// allocate memory and load resources
	
	// Lights
	// Textures
	Texture* txGlass = new Texture();
	txGlass->load("../assets/images/windowV.jpg", 122);
	gTextures.push_back(txGlass);

	// Objeto de textura de la foto a ser sacada
	Texture* foto = new Texture();
	gTextures.push_back(foto);

	// Box cover
	Texture* txBox = new Texture();
	Texture* txBoxInt = new Texture();
	txBox->load("../assets/images/container.jpg");
	gTextures.push_back(txBox);
	txBoxInt->load("../assets/images/papelE.png");
	gTextures.push_back(txBoxInt);

	// Ground
	Texture* txGround = new Texture();
	txGround->load("../assets/images/baldosaC.png");
	gTextures.push_back(txGround);

	// Star
	Texture* txStar = new Texture();
	txStar->load("../assets/images/baldosaP.png");
	gTextures.push_back(txStar);


	// Graphics objects (entities) of the scene
	gObjects.push_back(new RGBAxes(400.0));
	gObjects.push_back(new BoxCover(txBox, txBoxInt, false, 50)); // tiene que venir antes del glass si no no hay transparencia
	gObjects.push_back(new Ground(txGround, false, 100, 100, 4, 4));
	gObjects.push_back(new BoxOutline(txBox, txBoxInt, false, 50));
	gObjects.push_back(new Star3D(txStar, false, 20, 10, 10));


	gObjects.push_back(new GlassParapet(txGlass, false, 400));
	gObjects.push_back(new Photo(foto, false, 100, 100));
}

void Scene6::update()
{
	for (auto* o : gObjects)
		o->update();
}

