#include "CompRender.h"
#include "Rev_CoreSystems.h"
#include "CompTransform.h"

using namespace Rev;

CompRender::CompRender(GameObject* gameObj, CompTransform* transform, float color, int width, int height) :
	BaseComponent(gameObj),
	m_Transform{ transform }
{
	Vector3 pos = m_Transform->getPosition();

	m_Vertices =
	{
		//Bottom Left
		{ { pos.x - width,  pos.y - height, pos.z }, { color, color, color } },
		//Bottom Right
		{ { pos.x + width,  pos.y - height, pos.z }, { color, color, color } },
		//Top Left
		{ { pos.x - width,  pos.y + height, pos.z }, { color, color, color } },
		//Top Right
		{ { pos.x + width,  pos.y + height, pos.z }, { color, color, color } },
	};

	Rev_CoreSystems::pRevRender->SetupShader(m_Vertices, m_Indices);
}

void Rev::CompRender::SetupVertexShader(std::string vertexFile)
{
}

void Rev::CompRender::SetupPixelShader(std::string pixelFile)
{
}

const void CompRender::render()
{
	Rev_CoreSystems::pRevRender->DrawWindow();
}
