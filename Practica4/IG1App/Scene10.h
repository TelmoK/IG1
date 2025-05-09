#pragma once
#include "Scene.h"

class Scene10 : public Scene
{
public:
	Scene10() = default;

	void init() override;

	void rotate() override;
	void orbit() override;

	void setColor() override;

private:

	CompoundEntity* orbInventedNode;
	CompoundEntity* rotInventedNode;
};

