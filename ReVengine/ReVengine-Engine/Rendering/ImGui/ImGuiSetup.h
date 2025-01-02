#pragma once

#include "d3d11.h"

struct SDL_Window;

namespace RevDev
{
	class ImGuiSetup
	{
	public:
		ImGuiSetup();
		~ImGuiSetup();

		void InitWindow(int windowWidth, int windowHeight);
		void InitForSDL2(SDL_Window& window);
		void InitFor3D11(ID3D11Device& device, ID3D11DeviceContext& deviceContext);

		void Update();
	private:
		float m_ImguiWindowWidth;
		float m_ImguiWindowHeight;

		float m_WindowHeight;

	};
}