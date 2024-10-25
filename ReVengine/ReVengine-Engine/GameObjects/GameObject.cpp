#include "GameObject.h"
#include "BaseComponent.h"

using namespace Rev;

GameObject::GameObject()
{
}

GameObject::~GameObject()
{
}

void Rev::GameObject::update()
{
	for (auto& comp : m_Components)
	{
		comp->update();
	}
}
