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

	private:
		std::unique_ptr<RevDev::PhysicsImpl> m_PhysicsImpl;
	};
}