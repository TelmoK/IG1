#include "Scene8.h"

void Scene8::init()
{
	setGL(); // OpenGL settings

	gObjects.push_back(new RGBAxes(400.0));

	gObjects.push_back(new Sphere(50, 20, 20));
	//gObjects.push_back(new Toros(200, 50));
	//gObjects.push_back(new Disk(50, 250, 5, 40));
	//gObjects.push_back(new Cone(300, 250, 0, 5, 40));
	//gObjects.push_back(new WingAdvancedTIE());
	//gObjects.push_back(new TieFighter());

	//gObjects.push_back(new IndexedBox(300));
}

void Scene8::showNormals()
{
	for (auto* o : gObjects) {
		if (dynamic_cast<ColorMaterialEntity*>(o))
			dynamic_cast<ColorMaterialEntity*>(o)->toggleShowNormals();
	}
}
