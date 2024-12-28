#pragma once

#include "GameObjects/BaseComponent.h"
#include <glm/vec3.hpp>

namespace Rev
{
	class Physics;
}

namespace Rev
{
	class CompCollision : public Rev::BaseComponent
	{
	public:
		CompCollision(Rev::GameObject* gameObj, Rev::Physics* physicsHandle, bool staticObject, bool gravity = false, glm::vec3 size = { 1,1,1 }, glm::vec3 pos = { 0,0,0 });
		~CompCollision() = default;

	private:

	private:
		Rev::Physics* m_PhysicsHandle;

		glm::vec3 m_Position;
		glm::vec3 m_Size;

		int m_ColliderID;
		static int colliderCounter;
	};
}