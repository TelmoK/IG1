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

	for (Texture* tx : gTextures)
		delete tx;

	for (Light* l : gLights)
		delete l;
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

	for (Abs_Entity* e : gObjects)
		for (Light* l : gLights)
			l->unload(*Shader::get("light"));
}

void Scene::uploadLights() const // pode dar problema
{
	for(Abs_Entity* e : gObjects)
		for (Light* l : gLights)
			l->upload(*Shader::get("light"), e->modelMat());
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

	uploadLights();

	for (Abs_Entity* el : gObjects)
		el->render(cam.viewMat());

	for (Abs_Entity* tel : gTranslucidObjs)
		tel->render(cam.viewMat());
}
