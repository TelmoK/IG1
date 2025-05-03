#include "Scene8.h"

void Scene8::init()
{
	Scene::init();

	gObjects.push_back(new IndexedBox(300, glm::vec4(0, 0, 1, 1)));
}
