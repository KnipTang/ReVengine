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

	private:
		std::unique_ptr<RevDev::Physics_PhysX> m_PhysicsPhysX;
	};
}