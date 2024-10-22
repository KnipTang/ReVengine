#pragma once

#include <functional>;
#include <memory>

namespace RevDev {
	class RenderWindow;
}

namespace Rev
{
	class Rev_Sound;
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