#include "CompRender.h"
#include "Utils/Vertex.h"

using namespace Rev;

CompRender::CompRender(GameObject* gameObj, const std::vector<unsigned short> indices, const std::vector<Vertex> vertices) :
	BaseComponent(gameObj),
	m_Indices{ indices },
	m_Vertices{vertices}
{
}

const void CompRender::render()
{

}
