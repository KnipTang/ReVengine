#include "Camera.h"
#include "Utils/Vector3.h"
#include "Utils/ReV_Mat.h"

using namespace RevDev;

Camera::Camera() :
	m_Position{},
	m_Rotation{}
{
}

Camera::~Camera()
{

}

void Camera::Update()
{
	DirectX::XMVECTOR up = DirectX::XMVectorSet(0.0f, 1.0, 0.0, 1.0f);
	DirectX::XMVECTOR vecPosition = DirectX::XMLoadFloat3(&m_Position);
	DirectX::XMVECTOR lookAt = DirectX::XMVectorSet(0.0, 0.0, 1.0f, 1.0f);

	float pitch = m_Rotation.x * RevMat::DEG_TO_RAD_F;
	float yaw = m_Rotation.y * RevMat::DEG_TO_RAD_F;
	float roll = m_Rotation.z * RevMat::DEG_TO_RAD_F;

	DirectX::XMMATRIX rotationMatrix = DirectX::XMMatrixRotationRollPitchYaw(pitch, yaw, roll);

	lookAt = XMVector3TransformCoord(lookAt, rotationMatrix);
	up = XMVector3TransformCoord(up, rotationMatrix);

	lookAt = DirectX::XMVectorAdd(vecPosition, lookAt);

	m_ViewMatrix = DirectX::XMMatrixLookAtLH(vecPosition, lookAt, up);
}

void Camera::AddPitchInput(float input)
{
	m_Rotation.x += input;
}

void Camera::AddYawInput(float input)
{
	m_Rotation.y += input;
}

void Camera::SetPosition(float x, float y, float z)
{
	m_Position = DirectX::XMFLOAT3(x, y, z);
}

void Camera::SetPosition(Vector3 pos)
{
	SetPosition(pos.x, pos.y, pos.z);
}

void Camera::SetRotation(float yaw, float pitch, float roll)
{
	m_Rotation = DirectX::XMFLOAT3(yaw, pitch, roll);
}

void Camera::SetRotation(Vector3 dir)
{
	SetRotation(dir.x, dir.y, dir.z);
}

Vector3 Camera::GetPosition() const
{
	return Vector3(m_Position.x, m_Position.y, m_Position.z);
}

Vector3 Camera::GetRotation() const
{
	return Vector3(m_Rotation.x, m_Rotation.y, m_Rotation.z);
}