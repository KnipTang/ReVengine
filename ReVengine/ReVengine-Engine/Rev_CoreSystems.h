#pragma once

#include <memory>

namespace Rev
{
	class Rev_Sound;
	class Rev_CoreSystems
	{
	public:
		Rev_CoreSystems() = delete;
		~Rev_CoreSystems() = delete;


		//Core systems //Static vars can't depend on each other because static party alcoholism problem(its a drunk driving issue)
		static inline std::unique_ptr<Rev_Sound> pRevSound = std::make_unique<Rev_Sound>();
	private:
	};
}