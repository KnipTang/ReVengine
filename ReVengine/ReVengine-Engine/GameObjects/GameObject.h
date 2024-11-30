#pragma once

#include <vector>
#include <memory>
#include <algorithm>
#include "BaseComponent.h"

namespace Rev
{
	template <class T>
	concept baseCompConcept = std::derived_from<T, BaseComponent>;

	class GameObject
	{
	public:
		GameObject();
		~GameObject();

		void update();
		void fixedUpdate();
		const void render();

		template <baseCompConcept T, typename... TArguments>
		T* addComponent(GameObject* gameObj, TArguments&&... args)
		{
			if (hasComponent<T>())
				return nullptr;

			std::unique_ptr<T> comp = std::make_unique<T>(gameObj, std::forward<TArguments>(args)...);
			m_Components.emplace_back(std::move(comp));

			return dynamic_cast<T*>(m_Components.back().get());
		}

		template <baseCompConcept T>
		const bool hasComponent()
		{
			for (const auto& comp : m_Components)
			{
				if (dynamic_cast<T*>(comp.get()))
					return true;
			}

			return false;
		}

		template <baseCompConcept T>
		T* getComponent()
		{
			for (auto& comp : m_Components)
			{
				if (auto derivedComp = dynamic_cast<T*>(comp.get()))
					return derivedComp;
			}

			return nullptr;
		}

		template <baseCompConcept T>
		void removeComponent()
		{
			m_Components.erase(
				std::remove_if(m_Components.begin(), m_Components.end(),
					[](const std::unique_ptr<BaseComponent>& comp) -> bool {
						return dynamic_cast<T*>(comp.get()) != nullptr;
					}),
				m_Components.end());
		}

		GameObject* AddChild(GameObject* childObj)
		{
			m_Children.emplace_back(childObj);
			return m_Children.back().get();
		}

		void RemoveChild(GameObject* childObj)
		{
			m_Children.erase(
				std::remove_if(m_Children.begin(), m_Children.end(), [childObj](std::unique_ptr<GameObject>& obj) -> bool
					{
						return obj.get() == childObj;
					}),
				m_Children.end()
			);
		}

		std::vector<std::unique_ptr<GameObject>>& GetChildren()
		{
			return m_Children;
		}

		void DisplayHierarchy()
		{
			std::printf("\tGameObject: %s\tID: %i\n", typeid(*this).name(), objID);
			std::for_each(m_Components.begin(), m_Components.end(), 
				[](std::unique_ptr<BaseComponent>& comp) -> bool
				{
					return std::printf("\t\tComponents: %s\n", typeid(*comp).name());
				}
			);
			std::ranges::for_each(m_Children,
				[](std::unique_ptr<GameObject>& child) -> void
				{
					child->DisplayHierarchy();
				}
			);
		}

		const int GetID() { return objID; }

	public:
		bool m_Enabled;

	private:
		std::vector<std::unique_ptr<BaseComponent>> m_Components;

		std::vector<std::unique_ptr<GameObject>> m_Children;

		static int objIDCounter;
		int objID;
	};
}