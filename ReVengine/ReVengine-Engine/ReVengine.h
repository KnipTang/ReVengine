#pragma once

#include <functional>;
#include <memory>

namespace Rev
{
	class Rev_Sound;
}

namespace RevDev 
{
	class RenderWindow;
}

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