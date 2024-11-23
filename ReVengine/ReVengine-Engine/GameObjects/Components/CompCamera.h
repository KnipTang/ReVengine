#pragma once

#include "GameObjects/BaseComponent.h"
#include <memory>

namespace RevDev
{
	class Camera;
}

namespace Rev
{
	class CompCamera : public BaseComponent
	{
	public:
		CompCamera(GameObject* gameObj);
		~CompCamera() = default;

		void update() override;

		void Turn(float x, float y);

		void AddYawInput(float input);
		void AddPitchInput(float input);

		RevDev::Camera* GetCamera() const { return m_Camera.get(); }
	private:
		std::unique_ptr<RevDev::Camera> m_Camera;

		float m_LookSensitivity;
	};
}