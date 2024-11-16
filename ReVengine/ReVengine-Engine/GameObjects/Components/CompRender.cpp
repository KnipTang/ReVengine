#include "CompRender.h"
#include "Rev_CoreSystems.h"
#include "CompTransform.h"
#include "Rendering/Texture.h"

using namespace Rev;

CompRender::CompRender(GameObject* gameObj, CompTransform* transform, Texture* texture, int windowWidth, int windowHeight) :
	BaseComponent(gameObj),
	m_Transform{ transform },
	m_MeshId{}
{
	Vector3 pos = m_Transform->getPosition();
	[[maybe_unused]] int width =texture->GetTextureDate()->ImageWidth;
	m_Vertices =
	{
		//Bottom Left
		{ { pos.x - windowWidth,  pos.y - windowHeight, pos.z }, { 0.f, 0.f } },
		//Bottom Right
		{ { pos.x + windowWidth,  pos.y - windowHeight, pos.z }, { 1.f, 0.f } },
		//Top Left
		{ { pos.x - windowWidth,  pos.y + windowHeight, pos.z }, { 0.f, 1.f } },
		//Top Right
		{ { pos.x + windowWidth,  pos.y + windowHeight, pos.z }, { 1.f, 1.f } },
	};

	m_Indices =
	{
		0,1,2,
		2,1,3,
	};

	m_MeshId = Rev_CoreSystems::pRevRender->AddMesh(m_Vertices, m_Indices, texture);
}

const void CompRender::render()
{
	Rev_CoreSystems::pRevRender->DrawMesh(m_MeshId);
}
