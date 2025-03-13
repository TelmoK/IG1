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

	// Grass
	Texture* txGrass = new Texture();
	txGrass->load("../assets/images/grass_alpha.png");
	gTextures.push_back(txGrass);


	// Graphics objects (entities) of the scene
	gObjects.push_back(new Ground(txGround, false, 100, 100, 4, 4));

	BoxCover* cover = new BoxCover(txBox, txBoxInt, false, 50);
	gObjects.push_back(cover); // tiene que venir antes del glass si no no hay transparencia

	BoxOutline* box = new BoxOutline(txBox, txBoxInt, false, 50);
	gObjects.push_back(box);

	box->setWPos(glm::vec3(200 - 50 / 2, 50 / 2, 200 - 50 / 2));
	cover->setWPos(glm::vec3(200 - 50 / 2, 50, 150));

	Star3D* star = new Star3D(txStar, false, 20, 10, 10);
	gObjects.push_back(star);
	star->setWPos(glm::vec3(200 - 50 / 2, 50, 75));

	gObjects.push_back(new Photo(foto, false, 100, 100));

	// Translucid objects
	gTranslucidObjs.push_back(new GlassParapet(txGlass, false, 400));

	Grass* grass = new Grass(txGrass, false, 30, 30);
	grass->setWPos(glm::vec3(125, 15, -125));
	gTranslucidObjs.push_back(grass);
}

void Scene6::update()
{
	for (auto* o : gObjects)
		o->update();

	for (auto* o : gTranslucidObjs)
		o->update();
}


void Scene6::printscreen()
{
	for (auto* o : gObjects) {
		if (dynamic_cast<Photo*>(o))
			dynamic_cast<Photo*>(o)->save("printScreen.bmp");
	}
}

