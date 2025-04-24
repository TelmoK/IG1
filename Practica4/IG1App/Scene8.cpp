#include "Scene8.h"

void Scene8::init()
{
	setGL(); // OpenGL settings

	gObjects.push_back(new RGBAxes(400.0));

	gObjects.push_back(new IndexedBox(300));
}

void Scene8::showNormals()
{
	for (auto* o : gObjects) {
		if (dynamic_cast<ColorMaterialEntity*>(o))
			dynamic_cast<ColorMaterialEntity*>(o)->toggleShowNormals();
	}
}
