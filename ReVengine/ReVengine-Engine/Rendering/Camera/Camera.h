#pragma once

#include <directxmath.h>

struct Vector3;

namespace RevDev
{
	class Camera
	{
	public:
		Camera();
		~Camera();

		void Update();

		DirectX::XMMATRIX GetViewMatrix() const { return m_ViewMatrix; };

		void SetPosition(float x, float y, float z);
		void SetPosition(Vector3 pos);
		void SetRotation(float x, float y, float z);
		void SetRotation(Vector3 dir);

		Vector3 GetPosition() const;
		Vector3 GetRotation() const;
	private:
		DirectX::XMFLOAT3 m_Position;
		DirectX::XMFLOAT3 m_Rotation;

		DirectX::XMMATRIX m_ViewMatrix;
	};
}