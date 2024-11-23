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

		RevDev::Camera* GetCamera() const { return m_Camera.get(); }
	private:
		std::unique_ptr<RevDev::Camera> m_Camera;
	};
}