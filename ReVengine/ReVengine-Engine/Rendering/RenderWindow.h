#pragma once

#include <memory>
#include <functional>

namespace RevDev
{
	class WindowHandler_D3D11;
}

struct SDL_Window;

namespace RevDev
{
	class RenderWindow
	{
	public:
		RenderWindow();
		~RenderWindow();

		bool InitWindow(int windowWidth, int windowHeight);
		void DrawWindow();
		bool UpdateWindow();

		void RipWindow();

	private:

		std::unique_ptr<WindowHandler_D3D11> creatorGod;

		//The window we'll be rendering to
		std::unique_ptr<SDL_Window, std::function<void(SDL_Window*)>> window;
	};
}