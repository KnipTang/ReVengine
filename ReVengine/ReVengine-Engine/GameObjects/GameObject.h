#pragma once

#include <vector>
#include <memory>

namespace Rev
{
	class BaseComponent;
}

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
		T* addComponent(GameObject* gameObj, const TArguments&... args)
		{
			if (hasComponent<T>())
				return nullptr;

			std::unique_ptr<T> comp = std::make_unique<T>(gameObj, args...);
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
					[](const std::unique_ptr<BaseComponent>& comp) {
						return dynamic_cast<T*>(comp.get()) != nullptr;
					}),
				m_Components.end());
		}

		const int GetID() { return objID; }
	private:
		std::vector<std::unique_ptr<BaseComponent>> m_Components;
		static int objIDCounter;
		int objID;
	};
}