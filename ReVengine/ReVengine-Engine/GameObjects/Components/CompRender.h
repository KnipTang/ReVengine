#pragma once

#include "GameObjects/BaseComponent.h"
#include <vector>
#include <string>
#include "Utils/Vertex.h"

//struct Vertex;
namespace Rev
{
	class CompTransform;
}

namespace Rev
{
	class CompRender : public BaseComponent
	{
	public:
		CompRender(GameObject* gameObj, CompTransform* transform, float color, int width = 1, int height = 1);
		~CompRender() {};

		void SetupVertexShader(std::string vertexFile);
		void SetupPixelShader(std::string pixelFile);

		const void render() override;
	private:
		CompTransform* m_Transform;

		std::vector<Vertex> m_Vertices;

		std::vector<unsigned short> m_Indices =
		{
			0,1,2,
			2,1,3,
		};
	};
}