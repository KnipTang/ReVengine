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
		CompRender(GameObject* gameObj, CompTransform* transform, float color, int m_WindowWidth = 1, int m_WindowHeight = 1);
		~CompRender() {};

		const void render() override;
	private:
		CompTransform* m_Transform;

		std::vector<Vertex> m_Vertices;

		std::vector<unsigned short> m_Indices;

		uint8_t m_MeshId;
	};
}