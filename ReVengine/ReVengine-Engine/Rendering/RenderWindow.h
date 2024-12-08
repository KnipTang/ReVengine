#pragma once

#include <memory>
#include <functional>
#include <DirectXMath.h>
#include "Camera/Camera.h"
#include "glm/matrix.hpp"

namespace Rev
{
	class Texture;
}

namespace RevDev
{
	class WindowHandler_D3D11;
	class Mesh;
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

		bool InitWindow(int windowWidth, int windowHeight, float nearZ, float farZ);

		uint32_t AddMesh(const std::vector<Vertex> vertices, const std::vector<unsigned short> indices, Rev::Texture* texture);
		void DrawMesh(uint32_t meshId, const glm::mat4 modelMatrix, const DirectX::XMMATRIX viewMatrix);

		bool UpdateWindow();

		void RipWindow();

		void LoadTexture();

		DirectX::XMMATRIX getProjectionMatrix();
		DirectX::XMMATRIX getWorldMatrix();
	private:

		std::unique_ptr<WindowHandler_D3D11> m_CreatorGod;

		//The window we'll be rendering to
		std::unique_ptr<SDL_Window, std::function<void(SDL_Window*)>> m_Window;

		std::vector<std::unique_ptr<Mesh>> m_Meshes;

		//The size of each vertex in mem, this way the gpu knows how many bytes there are in each vertex
		uint32_t m_VertexStride;
		//OffSet between vertecies
		uint32_t m_VertexOffset = 0;

		int m_WindowWidth;
		int m_WindowHeight;

		DirectX::XMMATRIX m_ProjectionMatrix;
	};
}