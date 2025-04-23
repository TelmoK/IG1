#include "Scene9.h"

void Scene9::init()
{
	setGL(); // OpenGL settings
	
	gObjects.push_back(new TieFighter());
}
