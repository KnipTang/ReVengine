#include "GameObject.h"
#include "BaseComponent.h"
#include <typeinfo>
#include <string>

using namespace Rev;

int GameObject::objIDCounter = 0;

GameObject::GameObject() :
	objID{objIDCounter++}
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