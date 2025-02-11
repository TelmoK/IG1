#include "Scene0.h"
#include <glm/gtc/matrix_transform.hpp>

void Scene0::init()
{
	setGL(); // OpenGL settings

	// allocate memory and load resources
	// Lights
	// Textures

	// Graphics objects (entities) of the scene
	gObjects.push_back(new RGBAxes(400.0));
	gObjects.push_back(new RegularPolygon(3, 100, glm::dvec4(0, 255, 255, 1)));
	gObjects.push_back(new RegularPolygon(100, 100, glm::dvec4(255, 0, 255, 1)));
	
	RGBTriangle* rgbTriangle = new RGBTriangle(20);

	rgbTriangle->setModelMat(glm::translate(rgbTriangle->modelMat(), {100, 0, 0}));

	gObjects.push_back(rgbTriangle);
}