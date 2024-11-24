#include "CompTransform.h"
#include <iostream>
#include "Utils/ReV_Mat.h"
#include <glm/gtc/matrix_transform.hpp>

using namespace Rev;

CompTransform::CompTransform(GameObject* gameObj, glm::vec3 position, glm::quat rotation/*, Vector3 scale*/) :
	BaseComponent(gameObj),
	m_Position{position},
	m_Rotation{rotation}
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
	glm::vec3 beforePos = m_Position;
	glm::vec3 movementDir = GetForwardVector();
	Move(movementDir, input * speed);
	printf("Pos: dx=%f, dy=%f, dz=%f\n", m_Position.x, m_Position.y, m_Position.z);
	glm::vec3 diffV = beforePos - m_Position;
	float diff = diffV.x + diffV.y + diffV.z;
	printf("Pos Diff: dx=%f\n", diff);

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
	m_Rotation.y += input;
}

void CompTransform::AddYawInput(float input)
{
	m_Rotation.x += input;
}

glm::vec3 CompTransform::GetForwardVector()
{
	float pitch = m_Rotation.x * RevMat::DEG_TO_RAD_F;
	float yaw = m_Rotation.y * RevMat::DEG_TO_RAD_F;

	float cosPitch = cos(pitch);
	float sinPitch = sin(pitch);
	float cosYaw = cos(yaw);
	float sinYaw = sin(yaw);

	glm::vec3 forward;
	forward.x = cosPitch * sinYaw;
	forward.y = sinPitch;
	forward.z = cosPitch * cosYaw;

	forward = glm::normalize(forward);

	return forward;
}

glm::vec3 CompTransform::GetRightVector()
{
	float yaw = m_Rotation.y * RevMat::DEG_TO_RAD_F;
	float roll = m_Rotation.z * RevMat::DEG_TO_RAD_F;

	float cosYaw = cos(yaw);
	float sinYaw = sin(yaw);
	float cosRoll = cos(roll);
	float sinRoll = sin(roll);

	glm::vec3 right;
	right.x = cosYaw * cosRoll;
	right.y = sinRoll;
	right.z = sinYaw * cosRoll;

	right = glm::normalize(right);

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

void CompTransform::SetRotation(glm::quat dir)
{
	m_Rotation = dir;
}

glm::quat& CompTransform::GetRotation()
{
	return m_Rotation;
}

glm::mat4 CompTransform::GetWorldMatrix()
{
	m_WorldMatrix = glm::translate(glm::mat4(1.0f), m_Position) * glm::mat4_cast(m_Rotation);
	return m_WorldMatrix;
}