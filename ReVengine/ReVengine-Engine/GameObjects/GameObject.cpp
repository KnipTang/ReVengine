#include "GameObject.h"
#include "BaseComponent.h"
#include <typeinfo>
#include <string>

using namespace Rev;

GameObject::GameObject()
{
}

GameObject::~GameObject()
{
}

void GameObject::update()
{
	for (auto& comp : m_Components)
	{
		comp->update();
	}
}