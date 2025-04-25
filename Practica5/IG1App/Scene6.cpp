#include "Scene6.h"
#include "IG1App.h"


void Scene6::init()
{
	setGL(); // OpenGL settings

	// allocate memory and load resources
	
	// Lights
	// Textures ---------------------------------------------------------------
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


	// Dimensions and popsitions ----------------------------------------------------
	
	// Ground
	GLdouble groundWidth = 100;
	GLdouble groundHeight = 100;
	GLuint rw = 4; 
	GLuint rh = 4;

	// Box and cover
	GLdouble boxLength = 50; // box and cover side:
	glm::vec3 boxPos = {
		(groundWidth * rw - boxLength) / 2 - 1, // el -1 es para no clippear con el glass
		boxLength / 2,
		(groundHeight * rh - boxLength) / 2 - 1 // el -1 es para no clippear con el glass
	};
	glm::vec3 boxCoverPos = {
		boxPos.x,
		boxLength + boxLength / 2, // altura de la caja más la mitad de la caja (centro de la tapa)
		boxPos.z - boxLength / 2
	};

	// Star
	GLdouble re = 20; // external radius
	GLuint np = 10; // number of points
	GLdouble zDistance = 10; // height
	glm::vec3 startPos = { boxPos.x, 100, boxPos.z };

	// Grass
	GLdouble grassWidth = 30;
	GLdouble grassHeight = 30;
	glm::vec3 grassPos = { 125, 15, -125 };

	// Glass
	GLdouble glassWidth = 400;


	// Graphics objects (entities) of the scene ------------------------------------
	gObjects.push_back(new RGBAxes(400.0));

	Ground* ground = new Ground(txGround, false, groundWidth, groundHeight, rw, rh);
	gObjects.push_back(ground);

	BoxCover* boxCover = new BoxCover(txBox, txBoxInt, false, boxLength);
	gObjects.push_back(boxCover);
	boxCover->setWPos(boxCoverPos);

	BoxOutline* box = new BoxOutline(txBox, txBoxInt, false, boxLength);
	gObjects.push_back(box);
	box->setWPos(boxPos);

	Star3D* star = new Star3D(txStar, false, re, np, zDistance);
	gObjects.push_back(star);
	star->setWPos(startPos);


	Photo* photo = new Photo(foto, false, 100, 100);
	gObjects.push_back(photo);
	photo->setWPos(glm::vec3(0, 0, -1));

	// Translucid objects
	Grass* grass = new Grass(txGrass, false, grassWidth, grassHeight);
	grass->setWPos(grassPos);
	gTranslucidObjs.push_back(grass);

	gTranslucidObjs.push_back(new GlassParapet(txGlass, false, glassWidth));
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

