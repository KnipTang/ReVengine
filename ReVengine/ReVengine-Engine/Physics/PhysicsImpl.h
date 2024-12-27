#pragma once

#include <memory>
#include <glm/vec3.hpp>

namespace RevDev
{
	class Physics_PhysX;
}

namespace RevDev
{
	class PhysicsImpl
	{
	public:
		PhysicsImpl();
		~PhysicsImpl();

		void Init();
		void Simulate(float fixedDeltaTime);

		void CreateStatic(glm::vec3 pos, glm::vec3 size);
		void CreateDynamic(glm::vec3 pos, glm::vec3 size, bool gravity);

	private:
		std::unique_ptr<RevDev::Physics_PhysX> m_PhysicsPhysX;
	};
}