#include "Scene11.h"

void Scene11::init()
{
	setGL(); // OpenGL settings

	// allocate memory and load resources
	// Lights
	gLights.push_back(new DirLight());
	// Textures

	//Materials
	Material copper_material; // needs to call setCopper() to initialize parameters. These parameters are used to set the uniforms at th render of the entity when called mMaterial.upload
	copper_material.setCopper();

	// Graphics objects (entities) of the scene
	gObjects.push_back(new RGBAxes(400.0));

	Sphere* s = new Sphere(50, 20, 30, glm::vec4(1, 1, 0, 1));
	s->setWPos(glm::vec3(0, 0, 150));
	gObjects.push_back(s);


	SphereWithMaterial* swm = new SphereWithMaterial(50, 20, 30);
	swm->setWPos(glm::vec3(150, 0, 0));

	swm->setMaterial(copper_material);

	gObjects.push_back(swm);
}
