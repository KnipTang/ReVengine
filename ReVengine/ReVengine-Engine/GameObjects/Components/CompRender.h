#pragma once

#include "GameObjects/BaseComponent.h"
#include <vector>

struct Vertex;

namespace Rev
{
	class CompRender : public BaseComponent
	{
	public:
		CompRender(GameObject* gameObj, const std::vector<unsigned short> indices, const std::vector<Vertex> vertices);
		~CompRender() {};

		const void render() override;
	private:
		const std::vector<unsigned short> m_Indices;
		const std::vector<Vertex> m_Vertices;
	};
}