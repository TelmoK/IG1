#pragma once
#include "Scene.h"

class Scene6 : public Scene
{
public:
	Scene6() = default;

	void init() override;
	void update() override;

	void printscreen() override;
};

