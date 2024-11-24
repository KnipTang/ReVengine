#pragma once

#include "GameObjects/BaseComponent.h"
#include <vector>
#include <string>
#include "Utils/Vertex.h"

//struct Vertex;
namespace Rev
{
	class CompTransform;
	class CompCamera;
	class Texture;
}

namespace Rev
{
	class CompRender : public BaseComponent
	{
	public:
		CompRender(GameObject* gameObj, CompTransform* transform, CompCamera* camera, Texture* texture, float widthTexture = 1, float heightTexture = 1);
		~CompRender() {};

		const void render() override;
	private:
		CompTransform* m_TransformComp;
		CompCamera* m_CameraComp;

		std::vector<Vertex> m_Vertices;
		std::vector<unsigned short> m_Indices;

		uint32_t m_MeshId;
	};
}