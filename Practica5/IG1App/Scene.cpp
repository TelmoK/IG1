#include "Scene.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace glm;

void
Scene::init()
{
	setGL(); // OpenGL settings

	// allocate memory and load resources
	// Lights
	mGlobalLight = new DirLight();
	mGlobalLight->setDirection(glm::vec3(-1, -1, -1));
	gLights.push_back({ mGlobalLight, ON });

	// Textures

	// Graphics objects (entities) of the scene
	gObjects.push_back(new RGBAxes(400.0));
}

Scene::~Scene()
{
	destroy();
	resetGL();
}

void
Scene::destroy()
{ // release memory and resources

	for (Abs_Entity* el : gObjects)
		delete el;

	gObjects.clear();

	for (Abs_Entity* tel : gTranslucidObjs)
		delete tel;

	gTranslucidObjs.clear();

	for (Texture* tx : gTextures)
		delete tx;

	gTextures.clear();

	for (auto& [light, state] : gLights)
		delete light;

	gLights.clear();
}

void
Scene::load()
{
	setColor(); // background color

	for (Abs_Entity* obj : gObjects)
		obj->load();

	for (Abs_Entity* tobj : gTranslucidObjs)
		tobj->load();
}

void
Scene::unload()
{

	for (Abs_Entity* obj : gObjects)
		obj->unload();

	for (Abs_Entity* tobj : gTranslucidObjs)
		tobj->unload();

	for (auto& [light, state] : gLights)
		light->unload(*Shader::get("light"));
}

void Scene::uploadLights(Camera const& cam) const
{
	Shader* s = Shader::get("light"); // We get the shader: a pointer to the shader "light" so we can use it = set as a context to setUniforms = upload uniform data
	s->use();

	//for(Abs_Entity* e : gObjects) // Objects don't have light. Light interact with objects, but are "owned" by the scene. 
	// ! Lights are used to set shader parameters !
	for (auto& [light, state] : gLights) {
		if (state == ON)
			light->upload(*s, cam.viewMat()); // We upload the shader
	}

}

void Scene::showNormals()
{
	for (auto* o : gObjects) {
		if (dynamic_cast<ColorMaterialEntity*>(o))
			dynamic_cast<ColorMaterialEntity*>(o)->toggleShowNormals();
	}
}

void Scene::toggleLight(Light* light)
{
	// Searches for the light requested to turn ON or OFF
	for (auto& [plight, pstate] : gLights) {
		if (plight == light) // change light state ON/OFF
			pstate = !pstate;
		if (pstate == OFF)
			plight->unload(*Shader::get("light")); // Unloads shader data if OFF
	}
}

void Scene::toggleLightWithKey_R()
{
	toggleLight(mGlobalLight);
}

void
Scene::setGL()
{
	// OpenGL basic setting
	setColor(); // background color
	glEnable(GL_DEPTH_TEST);          // enable Depth test
}
void
Scene::resetGL()
{
	glClearColor(.0, .0, .0, .0); // background color (alpha=1 -> opaque)
	glDisable(GL_DEPTH_TEST);     // disable Depth test
}

void Scene::setColor()
{
	glClearColor(0.6, 0.7, 0.8, 1.0); // background color (alpha=1 -> opaque)
}

void
Scene::render(Camera const& cam) const
{
	cam.upload();
	uploadLights(cam);

	for (Abs_Entity* el : gObjects) {
		el->render(cam.viewMat());
	}

	for (Abs_Entity* tel : gTranslucidObjs)
		tel->render(cam.viewMat());
}
