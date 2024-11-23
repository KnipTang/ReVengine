#include "InputManager.h"
#include "GameObjects/Components/CompInput.h"

using namespace RevDev;

InputManager::InputManager() : 
	m_MouseRelativeMotion{ std::make_unique<MouseRelativeMotion>() }
{

}

InputManager::~InputManager()
{

}

void InputManager::SubscribeInputComp(Rev::CompInput* inputComp)
{
	m_SubscriptedInputComps.emplace_back(inputComp);
}

void InputManager::HandleKeyDown(SDL_Scancode key)
{
	for (auto&& comp : m_SubscriptedInputComps)
	{
		comp->Execute(key);
	}
}

void InputManager::HandleMouseRelativeMotion(int x, int y)
{
	m_MouseRelativeMotion->x = x;
	m_MouseRelativeMotion->y = y;

	printf("Relative Mouse Movement: dx=%d, dy=%d\n", x, y);
}
