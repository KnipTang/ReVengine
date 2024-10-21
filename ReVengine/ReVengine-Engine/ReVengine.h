#pragma once

#include "functional";
#include "Rendering/RenderWindow.h"
#include <memory>

namespace Rev
{
	class ReVengine
	{
	public:
		ReVengine(int windowWidth, int windowHeight);
		~ReVengine();

		void Run(const std::function<void()>& GameRun);

	private:
		std::unique_ptr<RevDev::RenderWindow> pRenderWindow;
	};
}