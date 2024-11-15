#include "CompRender.h"
#include "Rev_CoreSystems.h"
#include "CompTransform.h"

using namespace Rev;

CompRender::CompRender(GameObject* gameObj, CompTransform* transform, float color, int windowWidth, int windowHeight) :
	BaseComponent(gameObj),
	m_Transform{ transform },
	m_MeshId{}
{
	Vector3 pos = m_Transform->getPosition();

	m_Vertices =
	{
		//Bottom Left
		{ { pos.x - windowWidth,  pos.y - windowHeight, pos.z }, { color, color, color } },
		//Bottom Right
		{ { pos.x + windowWidth,  pos.y - windowHeight, pos.z }, { color, color, color } },
		//Top Left
		{ { pos.x - windowWidth,  pos.y + windowHeight, pos.z }, { color, color, color } },
		//Top Right
		{ { pos.x + windowWidth,  pos.y + windowHeight, pos.z }, { color, color, color } },
	};

	m_Indices =
	{
		0,1,2,
		2,1,3,
	};

	m_MeshId = Rev_CoreSystems::pRevRender->AddMesh(m_Vertices, m_Indices);
}

const void CompRender::render()
{
	Rev_CoreSystems::pRevRender->DrawMesh(m_MeshId);
}
