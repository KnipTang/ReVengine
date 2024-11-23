#include "CompTransform.h"
#include <iostream>
#include "Utils/ReV_Mat.h"

using namespace Rev;

CompTransform::CompTransform(GameObject* gameObj, Vector3 position, Vector3 rotation/*, Vector3 scale*/) :
	BaseComponent(gameObj),
	m_Position{position},
	m_Rotation{rotation}
{

}

void CompTransform::update()
{
	printf("Relative Mouse Movement: dx=%f, dy=%f, dz=%f\n", m_Position.x, m_Position.y, m_Position.z);
}

void CompTransform::Move(Vector3 dir, float speed)
{
	m_Position += dir * speed;
}

void CompTransform::MoveForward(int input, float speed)
{
	Vector3 movementDir = GetForwardVector() + GetRightVector();
	Move(movementDir, input * speed);
}

void CompTransform::MoveRight(int input, float speed)
{
	Vector3 movementDir = GetRightVector();
	Move(movementDir, input * speed);
}

void CompTransform::SetPosition(Vector3 pos)
{
	m_Position = pos;
}

Vector3 CompTransform::GetPosition()
{
	return m_Position;
}

Vector3 CompTransform::GetForwardVector()
{
	float pitch = m_Rotation.x * RevMat::DEG_TO_RAD_F;
	float yaw = m_Rotation.y * RevMat::DEG_TO_RAD_F;

	float cosPitch = cos(pitch);
	float sinPitch = sin(pitch);
	float cosYaw = cos(yaw);
	float sinYaw = sin(yaw);

	Vector3 forward;
	forward.x = cosPitch * sinYaw;
	forward.y = sinPitch;
	forward.z = cosPitch * cosYaw;

	forward = forward.Normalized();

	return forward;
}

Vector3 CompTransform::GetRightVector()
{
	float yaw = m_Rotation.y * RevMat::DEG_TO_RAD_F;
	float roll = m_Rotation.z * RevMat::DEG_TO_RAD_F;

	float cosYaw = cos(yaw);
	float sinYaw = sin(yaw);
	float cosRoll = cos(roll);
	float sinRoll = sin(roll);

	Vector3 right;
	right.x = cosYaw * cosRoll;
	right.y = sinRoll;
	right.z = sinYaw * cosRoll;

	right = right.Normalized();

	return right;
}