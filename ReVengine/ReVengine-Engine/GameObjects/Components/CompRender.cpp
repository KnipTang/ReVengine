#include "CompRender.h"
#include "Rev_CoreSystems.h"

using namespace Rev;

CompRender::CompRender(GameObject* gameObj) :
	BaseComponent(gameObj)
{
}

CompRender::CompRender(GameObject* gameObj, const std::vector<unsigned short> indices, const std::vector<Vertex> vertices) :
	BaseComponent(gameObj),
	m_Indices{ indices },
	m_Vertices{ vertices }
{
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
