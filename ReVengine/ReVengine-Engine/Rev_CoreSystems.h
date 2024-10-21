#pragma once

#include <memory>

namespace Rev
{
	class Rev_Sound;
	class Rev_CoreSystems
	{
	public:
		Rev_CoreSystems();
		~Rev_CoreSystems();


		//Core systems
		std::unique_ptr<Rev_Sound> pRevSound;
	private:
	};
}