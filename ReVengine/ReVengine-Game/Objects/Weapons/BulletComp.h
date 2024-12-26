#pragma once
#include "GameObjects/BaseComponent.h"
#include "glm/vec3.hpp"

namespace Rev
{
	class CompTransform;
}

class BulletComp : public Rev::BaseComponent
{
public:
	BulletComp(Rev::GameObject* gameObj, float speed);
	~BulletComp();

	void fixedUpdate([[maybe_unused]] float fixedDeltaTime) override;

private:
	Rev::CompTransform* m_Transform;
	
	glm::vec3 m_StartDirection;
	float m_Speed;
};