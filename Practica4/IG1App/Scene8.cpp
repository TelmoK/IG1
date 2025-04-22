#include "Scene8.h"

void Scene8::init()
{
	setGL(); // OpenGL settings

	gObjects.push_back(new RGBAxes(400.0));

	//gObjects.push_back(new Sphere(50, 20, 20));
	gObjects.push_back(new Disk(50, 250, 5, 40));

	//gObjects.push_back(new IndexedBox(glm::dvec4(0, 0, 255, 255)));
}

void Scene8::showNormals()
{
	for (auto* o : gObjects) {
		if (dynamic_cast<IndexedBox*>(o))
			dynamic_cast<IndexedBox*>(o)->toggleShowNormals();
	}
}
