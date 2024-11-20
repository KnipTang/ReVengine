#include "Camera.h"
#include "Utils/Vector3.h"

using namespace RevDev;

Camera::Camera() :
	m_Position{},
	m_Rotation{}
{
	Update();
}

Camera::~Camera()
{

}

void Camera::Update()
{
	//DirectX::XMVECTOR up, positionv, lookAt;
	//float yaw, pitch, roll;
	//DirectX::XMMATRIX rotationMatrix;

	//up = DirectX::XMVectorSet(0.0f, 1.0, 0.0, 1.0f);
	//positionv = DirectX::XMLoadFloat3(&m_Position);
	//lookAt = DirectX::XMVectorSet(0.0, 0.0, 1.0f, 1.0f);

	//pitch = m_Rotation.x * 0.0174532f;
	//yaw = m_Rotation.y * 0.0174532f;
	//roll = m_Rotation.z * 0.0174532f;

	//rotationMatrix = DirectX::XMMatrixRotationRollPitchYaw(pitch, yaw, roll);

	//lookAt = XMVector3TransformCoord(lookAt, rotationMatrix);
	//up = XMVector3TransformCoord(up, rotationMatrix);

	//lookAt = positionv + lookAt;

	m_ViewMatrix = DirectX::XMMatrixIdentity();
	m_ViewMatrix = DirectX::XMMatrixMultiply(m_ViewMatrix, DirectX::XMMatrixTranslation(0.0f, 0.0f, 10.0f));
}

void Camera::SetPosition(float x, float y, float z)
{
	m_Position = DirectX::XMFLOAT3(x, y, z);
}

void Camera::SetPosition(Vector3 pos)
{
	SetPosition(pos.x, pos.y, pos.z);
}

void Camera::SetRotation(float x, float y, float z)
{
	m_Rotation = DirectX::XMFLOAT3(x, y, z);
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