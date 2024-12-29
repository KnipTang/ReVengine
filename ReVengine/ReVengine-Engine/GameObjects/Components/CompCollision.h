#pragma once

#include "GameObjects/BaseComponent.h"
#include <glm/vec3.hpp>
#include <iostream>
#include <functional>

namespace Rev
{
	class Physics;
	class CompTransform;
}

namespace Rev
{
	class CompCollision : public Rev::BaseComponent
	{
	public:
		CompCollision(Rev::GameObject* gameObj, Rev::Physics* physicsHandle, std::function<void(Rev::CompCollision* other)> collisionFnc, bool staticObject, bool gravity = false, glm::vec3 size = { 1,1,1 }, glm::vec3 pos = { 0,0,0 });
		~CompCollision();

		void update([[maybe_unused]] float deltaTime) override;

		int GetID() { return m_ColliderID; }
	public:
		std::function<void(Rev::CompCollision* other)> m_CollisionFnc;
	private:
		Rev::Physics* m_PhysicsHandle;

		Rev::CompTransform* m_TransformHandle;

		glm::vec3 m_Position;
		glm::vec3 m_Size;

		int m_ColliderID;
		static int colliderCounter;
	};
}