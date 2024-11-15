#pragma once

#include <memory>
#include <functional>

namespace Rev
{
	class Texture;
}

namespace RevDev
{
	class WindowHandler_D3D11;
}

struct SDL_Window;
struct Vertex;

namespace RevDev
{
	class RenderWindow
	{
	public:
		RenderWindow();
		~RenderWindow();

		bool InitWindow(int windowWidth, int windowHeight);
		void DrawMesh(uint32_t meshId);
		bool UpdateWindow();

		uint32_t AddMesh(const std::vector<Vertex> vertices, const std::vector<unsigned short> indices, Rev::Texture* texture);

		void RipWindow();

		void LoadTexture();
	private:

		std::unique_ptr<WindowHandler_D3D11> m_CreatorGod;

		//The window we'll be rendering to
		std::unique_ptr<SDL_Window, std::function<void(SDL_Window*)>> m_Window;

		int m_WindowWidth;
		int m_WindowHeight;
	};
}