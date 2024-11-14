#include "CompTransform.h"
#include <iostream>

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

void CompTransform::setPosition(Vector3 pos)
{
	m_Position = pos;
}

Vector3 CompTransform::getPosition()
{
	return m_Position;
}