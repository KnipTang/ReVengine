#pragma once

#include "functional";
#include "Rendering/RenderWindow.h"
#include <memory>

namespace Rev
{
	class Rev_Sound;
	class ReVengine
	{
	public:
		ReVengine(int windowWidth, int windowHeight);
		~ReVengine();

		void Run(const std::function<void()>& GameRun);

		//Core systems
		std::unique_ptr<Rev_Sound> pRevSound;
	private:
		std::unique_ptr<RevDev::RenderWindow> pRenderWindow;
	};
}