#pragma once

#include "GameObjects/BaseComponent.h"

namespace Rev
{
	class CompCollision : public Rev::BaseComponent
	{
	public:
		CompCollision(Rev::GameObject* gameObj);
		~CompCollision() = default;

		void fixedUpdate([[maybe_unused]] float deltaTime) override;
	private:
	};
}