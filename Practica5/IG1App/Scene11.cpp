#include "Scene11.h"

void Scene11::init()
{
	Scene::init();

	// allocate memory and load resources
	// Lights

	//DirLight* dirlight = new DirLight();
	////DirLightSimple* dirlight = new DirLightSimple();
	////dirlight->setDirection(glm::vec3(1, 1, 1));
	//gLights.push_back(dirlight);

	// Textures

	//Materials
	Material copper_material(glm::vec4(1, 1, 0, 1)); // needs to call setCopper() to initialize parameters. These parameters are used to set the uniforms at th render of the entity when called mMaterial.upload
	copper_material.setCopper();

	Material ruby_material;
	ruby_material.setGold();

	// Graphics objects (entities) of the scene

	Sphere* s = new Sphere(50, 20, 30);
	s->setWPos(glm::vec3(0, 0, 150));
	s->setMaterial(ruby_material);
	gObjects.push_back(s);


	Sphere* copperSphere = new Sphere(50, 20, 30);
	copperSphere->setWPos(glm::vec3(150, 0, 0));
	copperSphere->setMaterial(copper_material);
	gObjects.push_back(copperSphere);
}
