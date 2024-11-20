#pragma once
#include <memory>
#include <vector>
#include <SDL_scancode.h>

namespace Rev
{
	class CompInput;
}

namespace RevDev
{
	class InputManager
	{
	public:
		InputManager();
		~InputManager();

		void SubscribeInputComp(Rev::CompInput* inputComp);

		void HandleKeyDown(SDL_Scancode key);
	private:
		std::vector<Rev::CompInput*> m_SubscriptedInputComps;
	};
}