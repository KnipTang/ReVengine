#include "CompRender.h"
#include "Rev_CoreSystems.h"
#include "CompTransform.h"

using namespace Rev;

CompRender::CompRender(GameObject* gameObj, CompTransform* transform, float color, int m_WindowWidth, int m_WindowHeight) :
	BaseComponent(gameObj),
	m_Transform{ transform }
{
	Vector3 pos = m_Transform->getPosition();

	m_Vertices =
	{
		//Bottom Left
		{ { pos.x - m_WindowWidth,  pos.y - m_WindowHeight, pos.z }, { color, color, color } },
		//Bottom Right
		{ { pos.x + m_WindowWidth,  pos.y - m_WindowHeight, pos.z }, { color, color, color } },
		//Top Left
		{ { pos.x - m_WindowWidth,  pos.y + m_WindowHeight, pos.z }, { color, color, color } },
		//Top Right
		{ { pos.x + m_WindowWidth,  pos.y + m_WindowHeight, pos.z }, { color, color, color } },
	};

	m_Indices =
	{
		0,1,2,
		2,1,3,
	};

	Rev_CoreSystems::pRevRender->AddMesh(m_Vertices, m_Indices);
}

const void CompRender::render()
{
	Rev_CoreSystems::pRevRender->DrawMesh();
}
