#include "CompTransform.h"
#include <iostream>
#include "Utils/ReV_Mat.h"
#include <glm/gtc/matrix_transform.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/euler_angles.hpp>
#include "GameObjects/GameObject.h"
#include <algorithm>

using namespace Rev;

CompTransform::CompTransform(GameObject* gameObj, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale) :
	BaseComponent(gameObj),
	m_Position{position},
	m_Rotation{rotation},
	m_Scale{scale}
{

}

void CompTransform::update([[maybe_unused]] float deltaTime)
{

}

void CompTransform::Move(glm::vec3 dir, float speed)
{
	SetPosition(m_Position + dir * speed);
}

void CompTransform::MoveForward(int input, float speed)
{
	glm::vec3 movementDir = GetForwardVector();
	Move(movementDir, input * speed);
}

void CompTransform::MoveRight(int input, float speed)
{
	glm::vec3 movementDir = GetRightVector();
	Move(movementDir, input * speed);
}

void CompTransform::Turn(float x, float y)
{
	AddPitchInput(glm::radians(x));
	AddYawInput(glm::radians(y));
}

void CompTransform::AddPitchInput(float input)
{
	SetRotationRad(m_Rotation.x + input, m_Rotation.y, m_Rotation.z);
}

void CompTransform::AddYawInput(float input)
{
	SetRotationRad(m_Rotation.x, m_Rotation.y + input, m_Rotation.z);
}

glm::vec3 CompTransform::GetForwardVector()
{
	GetModelMatrix();
	const glm::vec3 forward = glm::vec3(m_ModelMatrix[2]);
	return forward;
}

glm::vec3 CompTransform::GetRightVector()
{
	GetModelMatrix();
	const glm::vec3 right = glm::vec3(m_ModelMatrix[0]);

	return right;
}

void CompTransform::SetPosition(float x, float y, float z)
{	
	SetPosition(glm::vec3(x, y, z));
}

void CompTransform::SetPosition(glm::vec3 pos)
{	
	m_Position = pos;

	if (m_GameObject->GetChildCount() > 0)
	{
		std::ranges::for_each(m_GameObject->GetChildren(),
			[pos](std::unique_ptr<GameObject>& child) -> void
			{
				child->transform->SetPosition(child->transform->m_LocalPosition + pos);
			});
	}
}

glm::vec3 CompTransform::GetPosition()
{
	return m_Position;
}

void CompTransform::SetRotationRad(float x, float y, float z)
{
	SetRotationRad(glm::vec3(x, y, z));
}

void CompTransform::SetRotationRad(glm::vec3 dir)
{
	m_Rotation = dir;
	m_Rotation = glm::mod(m_Rotation, glm::two_pi<float>());

	if (m_GameObject->GetChildCount() > 0)
	{
		std::ranges::for_each(m_GameObject->GetChildren(),
			[dir](std::unique_ptr<GameObject>& child) -> void
			{
				child->transform->SetRotationRad(child->transform->m_LocalRotation + dir);
			});
	}
}

void CompTransform::SetRotationDegree(float x, float y, float z)
{
	SetRotationDegree(glm::vec3(x, y, z));
}

void CompTransform::SetRotationDegree(glm::vec3 dir)
{
	SetRotationRad(glm::radians(dir));
}

glm::vec3 CompTransform::GetRotation()
{
	return m_Rotation;
}

glm::mat4 CompTransform::GetModelMatrix()
{
	glm::mat4 scaleMat = glm::scale(glm::mat4(1.0f), m_Scale);
	glm::mat4 rotationMat = glm::yawPitchRoll(m_Rotation.y, m_Rotation.x, m_Rotation.z);
	glm::mat4 positionMat = glm::translate(glm::mat4(1.0f), m_Position);
	m_ModelMatrix = scaleMat * rotationMat * positionMat;
	return m_ModelMatrix;
}