#pragma once

#include "GameObjects/BaseComponent.h"

namespace Rev
{
	class CompTest : public BaseComponent
	{
	public:
		CompTest(GameObject* gameObj);
		~CompTest() {};

		void update() override; // override is not requered to override a virtual funciton from base class, but its good practice

	private:
	};
}