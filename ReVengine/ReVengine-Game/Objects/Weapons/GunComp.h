#pragma once
#include "GameObjects/BaseComponent.h"
#include <functional>

namespace Rev
{
	class CompTransform;
}

class GunComp : public Rev::BaseComponent
{
public:
	GunComp(Rev::GameObject* gameObj, Rev::CompTransform* playerTransform, std::function<Rev::GameObject*()> bulletFunc);
	~GunComp();

	void Fire();

private:
	Rev::CompTransform* m_PlayerTransform;
	std::function<Rev::GameObject*()> m_BulletFunc;
};