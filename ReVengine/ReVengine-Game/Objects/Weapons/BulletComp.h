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
	BulletComp(Rev::GameObject* gameObj, Rev::CompTransform* transform);
	~BulletComp();

	void Init(glm::vec3 pos, glm::vec3 rotation);

	void fixedUpdate([[maybe_unused]] float fixedDeltaTime) override;

private:
	Rev::CompTransform* m_Transform;
};