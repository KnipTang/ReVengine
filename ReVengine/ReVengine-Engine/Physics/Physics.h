#pragma once

#include <memory>

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

	private:
		std::unique_ptr<RevDev::PhysicsImpl> m_PhysicsImpl;
	};
}