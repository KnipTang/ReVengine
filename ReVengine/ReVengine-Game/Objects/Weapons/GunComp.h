#pragma once
#include "GameObjects/BaseComponent.h"

namespace Rev
{
	class GameObject;
}

class GunComp : public Rev::BaseComponent
{
public:
	GunComp(Rev::GameObject* gameObj, Rev::GameObject* bullet);
	~GunComp();

	void Fire();

private:
	Rev::GameObject* m_Bullet;
};