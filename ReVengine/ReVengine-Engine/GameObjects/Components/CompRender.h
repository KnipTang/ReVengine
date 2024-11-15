#pragma once

#include "GameObjects/BaseComponent.h"
#include <vector>
#include <string>
#include "Utils/Vertex.h"

//struct Vertex;
namespace Rev
{
	class CompTransform;
	class Texture;
}

namespace Rev
{
	class CompRender : public BaseComponent
	{
	public:
		CompRender(GameObject* gameObj, CompTransform* transform, Texture* texture, float color, int windowWidth = 1, int windowHeight = 1);
		~CompRender() {};

		const void render() override;
	private:
		CompTransform* m_Transform;

		std::vector<Vertex> m_Vertices;

		std::vector<unsigned short> m_Indices;

		uint32_t m_MeshId;
	};
}