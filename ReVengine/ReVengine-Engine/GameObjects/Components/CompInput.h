#pragma once

#include <functional>
#include <unordered_map>
#include <SDL_scancode.h>
#include "GameObjects/BaseComponent.h"

namespace Rev
{
	class CompInput : public BaseComponent
	{
	public:
		CompInput(GameObject* gameObj);
		~CompInput() = default;

		void BindAction(SDL_Scancode key, std::function<void()> action);
		void Execute(SDL_Scancode key);
		
	private:
		using ActionMap = std::unordered_multimap<SDL_Scancode, std::function<void()>>;
		ActionMap m_Actions;


	};
}