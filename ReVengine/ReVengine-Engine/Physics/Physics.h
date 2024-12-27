#pragma once

#include <memory>
#include <glm/vec3.hpp>

namespace RevDev 
{
	class PhysicsImpl;
}

namespace Rev
{
	class Physics
	{
	public:
		Physics();
		~Physics();

		void Init();
		void Simulate(float fixedDeltaTime);

		void CreateStatic(glm::vec3 pos, glm::vec3 size);
		void CreateDynamic(glm::vec3 pos, glm::vec3 size, bool gravity);

	private:
		std::unique_ptr<RevDev::PhysicsImpl> m_PhysicsImpl;
	};
}