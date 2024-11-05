#include "CompTransform.h"

using namespace Rev;

CompTransform::CompTransform(GameObject* gameObj, Vector3 position, Vector3 rotation, Vector3 scale) :
	BaseComponent(gameObj),
	m_Position{position},
	m_Rotation{rotation},
	m_Scale{scale}
{

}

void CompTransform::update()
{
}
