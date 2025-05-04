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

	void toggleLightWithKey_T() override;
	void toggleLightWithKey_Y() override;
	void toggleLightWithKey_H() override;

private:

	CompoundEntity* orbInventedNode;
	CompoundEntity* rotInventedNode;

	PosLightXY* mPosLightXY = nullptr;
	SpotLightYZ* mSpotLightYZ = nullptr;
	SpotLight* mFighterLight = nullptr;
};

