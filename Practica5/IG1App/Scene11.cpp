#include "Scene11.h"

void Scene11::init()
{
	setGL(); // OpenGL settings

	// allocate memory and load resources
	// Lights
	gLights.push_back(new DirLight());
	// Textures

	// Graphics objects (entities) of the scene
	gObjects.push_back(new RGBAxes(400.0));


	gObjects.push_back(new Sphere(150, 20, 30));

	Sphere* s = new Sphere(150, 20, 30);
	s->setWPos(glm::vec3(350, 0, 0));
	gObjects.push_back(s);
}
