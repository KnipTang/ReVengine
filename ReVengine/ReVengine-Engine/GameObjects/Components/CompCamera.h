#pragma once

#include "GameObjects/BaseComponent.h"
#include <memory>

namespace RevDev
{
	class Camera;
}

namespace Rev
{
	class CompTransform;
}

namespace Rev
{
	class CompCamera : public BaseComponent
	{
	public:
		CompCamera(GameObject* gameObj, Rev::CompTransform* transform, bool flipControlls = false);
		~CompCamera() = default;

		void update() override;

		void Turn(float x, float y);

		RevDev::Camera* GetCamera() const { return m_Camera.get(); }
	private:
		std::unique_ptr<RevDev::Camera> m_Camera;

		Rev::CompTransform* m_Transform;

		float m_LookSensitivity;

		bool m_ControllsFlipped;
	};
}