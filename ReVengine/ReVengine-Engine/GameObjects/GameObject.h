#pragma once

#include <vector>
#include <memory>
#include <iostream>
namespace Rev
{
	class BaseComponent;
}

namespace Rev
{
	class GameObject
	{
	public:
		GameObject();
		~GameObject();

		void update();

		template <class T, typename... TArguments>
		const BaseComponent* addComponent(const TArguments&... args)
		{
			//Add to check if comp type is already in gameobject
			if (hasComponentType<T>())
				return nullptr;

			std::unique_ptr<BaseComponent> comp = std::make_unique<T>(args...);
			//hasComponentType(*comp.get());
			m_Components.emplace_back(std::move(comp));

			return m_Components.back().get();
		}

		template <class T>
		const bool hasComponentType()
		{
			for (const auto& comp : m_Components)
			{
				if (dynamic_cast<T*>(comp.get()))
					return true;
			}

			return false;
		}

		void removeComponent(std::unique_ptr<BaseComponent>&& component);
	private:
		std::vector<std::unique_ptr<BaseComponent>> m_Components;
	};
}