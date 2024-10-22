#pragma once

#include <memory>
#include <functional>

namespace RevDev
{
	class D3D11Creator;
}

struct SDL_Window;

namespace RevDev
{
	class RenderWindow
	{
	public:
		RenderWindow(int windowWidth, int windowHeight);
		~RenderWindow();

		bool InitWindow();

	private:
		int LoopWindow();
		int width;
		int height;

		std::unique_ptr<D3D11Creator> creatorGod;

		//The window we'll be rendering to
		std::unique_ptr<SDL_Window, std::function<void(SDL_Window*)>> window;
	};
}