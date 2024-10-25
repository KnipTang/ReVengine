#pragma once

#include <vector>
#include <memory>

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

			std::unique_ptr<BaseComponent> comp = std::make_unique<T>(args...);
			m_Components.emplace_back(std::move(comp));

			return m_Components.back().get();
		}

		void removeComponent(std::unique_ptr<BaseComponent>&& component);
	private:
		std::vector<std::unique_ptr<BaseComponent>> m_Components;
	};
}