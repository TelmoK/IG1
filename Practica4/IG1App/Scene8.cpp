#include "Scene8.h"

void Scene8::init()
{
	setGL(); // OpenGL settings

	gObjects.push_back(new RGBAxes(400.0));
	gObjects.push_back(new IndexedBox());
}
