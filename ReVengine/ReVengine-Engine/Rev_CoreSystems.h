#pragma once

#include <memory>
#include "Rendering/RenderWindow.h"
#include "Sound/Rev_Sound.h"
//
//namespace RevDev
//{
//	class RenderWindow;
//}

//namespace Rev
//{
//	class Rev_Sound;
//}

namespace Rev
{
	class Rev_CoreSystems
	{
	public:
		Rev_CoreSystems() = delete;
		~Rev_CoreSystems() = delete;

		//Core systems //Static vars can't depend on each other because static party problem
		static inline std::unique_ptr<Rev::Rev_Sound> pRevSound = std::make_unique<Rev::Rev_Sound>();
		static inline std::unique_ptr<RevDev::RenderWindow> pRevRender = std::make_unique<RevDev::RenderWindow>();
	private:
	};
}