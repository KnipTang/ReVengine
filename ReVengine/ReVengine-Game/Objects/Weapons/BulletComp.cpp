#include "BulletComp.h"
#include "GameObjects/Components/CompTransform.h"
#include "GameObjects/GameObject.h"
#include <iostream>

BulletComp::BulletComp(Rev::GameObject* gameObj, float speed) :
	Rev::BaseComponent(gameObj),
	m_Transform(gameObj->transform),
	m_StartDirection(gameObj->transform->GetRotation()),
	m_Speed(speed)
{

}

BulletComp::~BulletComp()
{
}

void BulletComp::fixedUpdate([[maybe_unused]] float fixedDeltaTime)
{
	std::cout << m_Transform->GetPosition().x << "\n";
	m_Transform->MoveForward(1, m_Speed);
}