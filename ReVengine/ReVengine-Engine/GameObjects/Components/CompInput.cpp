#include "CompInput.h"
#include "Rev_CoreSystems.h"
#include <utility>

using namespace Rev;

CompInput::CompInput(GameObject* gameObj) :
	BaseComponent(gameObj)
{
	Rev::Rev_CoreSystems::pInputManager->SubscribeInputComp(this);
}

void CompInput::BindAction(SDL_Scancode key, std::function<void()> action)
{
	m_Actions.emplace(key, action);
}

void CompInput::Execute(SDL_Scancode key)
{
	std::pair actionRange = m_Actions.equal_range(key);
	for (auto iterator = actionRange.first; iterator != actionRange.second; iterator++) {
		iterator->second();
	}
}