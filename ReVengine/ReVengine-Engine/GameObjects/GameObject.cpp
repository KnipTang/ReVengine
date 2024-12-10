#include "GameObject.h"
#include "BaseComponent.h"
#include "Components/CompTransform.h"

using namespace Rev;

int GameObject::objIDCounter = 0;

GameObject::GameObject() :
	m_Enabled{true},
	objID{objIDCounter++},
	m_ChildrenCount{0},
	m_Parent{nullptr}
{
	transform = addComponent<Rev::CompTransform>(this);
}

GameObject::~GameObject()
{
}

void GameObject::update(float deltaTime)
{
	for (auto&& comp : m_Components)
	{
		comp->update(deltaTime);
	}
	for (auto&& obj : m_Children)
	{
		obj->update(deltaTime);
	}
}

void GameObject::lateUpdate(float deltaTime)
{
	for (auto&& comp : m_Components)
	{
		comp->lateUpdate(deltaTime);
	}
	for (auto&& obj : m_Children)
	{
		obj->lateUpdate(deltaTime);
	}
}

void GameObject::fixedUpdate(float fixeDeltaTime)
{
	for (auto&& comp : m_Components)
	{
		comp->fixedUpdate(fixeDeltaTime);
	}
	for (auto&& obj : m_Children)
	{
		obj->fixedUpdate(fixeDeltaTime);
	}
}

const void GameObject::render()
{
	for (auto&& comp : m_Components)
	{
		comp->render();
	}
	for (auto&& obj : m_Children)
	{
		obj->render();
	}
}

GameObject* GameObject::AddChild(GameObject* childObj)
{
	childObj->SetParent(this);

	childObj->transform->m_LocalPosition = childObj->transform->GetPosition() - transform->GetPosition();
	childObj->transform->m_LocalRotation = childObj->transform->GetRotation() - transform->GetRotation();

	m_Children.emplace_back(childObj);

	m_ChildrenCount++;

	return m_Children.back().get();
}
