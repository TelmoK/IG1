#ifndef _H_Scene_H_
#define _H_Scene_H_

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "Camera.h"
#include "Entity.h"

#include <vector>

class Scene
{
public:
	Scene() = default;
	~Scene();

	Scene(const Scene& s) = delete;            // no copy constructor
	Scene& operator=(const Scene& s) = delete; // no copy assignment

	virtual void init();

	void render(Camera const& cam) const;
	virtual void update() {};

	// load or unload scene data into the GPU
	void load();
	void unload();

	virtual void printscreen() {};

protected:
	void destroy();
	void setGL();
	void resetGL();

	std::vector<Abs_Entity*> gObjects; // Entities (graphic objects) of the scene
	std::vector<Abs_Entity*> gTranslucidObjs; // Entities (translucid objects) of the scene
	std::vector<Texture*> gTextures; // Texturas de la escena
};

#endif //_H_Scene_H_
