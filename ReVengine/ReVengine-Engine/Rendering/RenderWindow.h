#pragma once

#include "SDL.h"

namespace RevDev
{
	class D3D11Creator;
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

		D3D11Creator* creatorGod;

		//The window we'll be rendering to
		SDL_Window* window = nullptr;
	};
}