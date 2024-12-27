#pragma once

#include <memory>

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

	private:
		std::unique_ptr<RevDev::Physics_PhysX> m_PhysicsPhysX;
	};
}