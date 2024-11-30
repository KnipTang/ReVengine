#include "BulletComp.h"
#include "GameObjects/Components/CompTransform.h"

BulletComp::BulletComp(Rev::GameObject* gameObj, Rev::CompTransform* transform) :
	Rev::BaseComponent(gameObj),
	m_Transform{transform}
{

}

BulletComp::~BulletComp()
{
}

void BulletComp::Init(glm::vec3 pos, glm::vec3 rotation)
{
	m_Transform->SetPosition(pos);
	m_Transform->SetRotationDegree(rotation);
}

void BulletComp::fixedUpdate([[maybe_unused]] float fixedDeltaTime)
{
	m_Transform->MoveForward(1, 0.1f);
}