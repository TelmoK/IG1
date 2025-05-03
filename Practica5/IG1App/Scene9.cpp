#include "Scene9.h"

void Scene9::init()
{
	Scene::init();

	gObjects.push_back(new TieFighter());
}

void Scene9::setColor()
{
	glClearColor(.0, .0, .0, .0);
}