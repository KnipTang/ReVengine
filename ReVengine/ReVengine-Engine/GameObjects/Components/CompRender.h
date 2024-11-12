#pragma once

#include "GameObjects/BaseComponent.h"
#include <vector>
#include <string>
#include "Utils/Vertex.h"

//struct Vertex;

namespace Rev
{
	class CompRender : public BaseComponent
	{
	public:
		CompRender(GameObject* gameObj);
		CompRender(GameObject* gameObj, const std::vector<unsigned short> indices, const std::vector<Vertex> vertices);
		~CompRender() {};

		void SetupVertexShader(std::string vertexFile);
		void SetupPixelShader(std::string pixelFile);

		const void render() override;
	private:
		const std::vector<unsigned short> m_Indices;
		const std::vector<Vertex> m_Vertices;
	};
}