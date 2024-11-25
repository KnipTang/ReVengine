#include "CompTransform.h"
#include <iostream>
#include "Utils/ReV_Mat.h"
#include <glm/gtc/matrix_transform.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/euler_angles.hpp>

using namespace Rev;

CompTransform::CompTransform(GameObject* gameObj, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale) :
	BaseComponent(gameObj),
	m_Position{position},
	m_Rotation{rotation},
	m_Scale{scale}
{

}

void CompTransform::update()
{

}

void CompTransform::Move(glm::vec3 dir, float speed)
{
	m_Position += dir * speed;
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
	AddPitchInput(x);
	AddYawInput(y);
}

void CompTransform::AddPitchInput(float input)
{
	m_Rotation.x += glm::radians(input);
	m_Rotation.x = glm::mod(m_Rotation.x, glm::two_pi<float>());
}

void CompTransform::AddYawInput(float input)
{
	m_Rotation.y += glm::radians(input);
	m_Rotation.y = glm::mod(m_Rotation.y, glm::two_pi<float>());
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

void CompTransform::SetPosition(glm::vec3 pos)
{
	m_Position = pos;
}

glm::vec3& CompTransform::GetPosition()
{
	return m_Position;
}

void CompTransform::SetRotation(glm::vec3 dir)
{
	m_Rotation = glm::radians(dir);
}

glm::vec3& CompTransform::GetRotation()
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