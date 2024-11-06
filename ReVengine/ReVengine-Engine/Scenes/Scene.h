#pragma once

#include <vector>
#include <memory>
#include <iostream>

namespace Rev
{
	class GameObject;
}

namespace Rev
{
	template <class T>
	concept gameObjectConcept = std::derived_from<T, GameObject>;

	class Scene
	{
	public:
		Scene();
		~Scene();

		void update();
		void fixedUpdate();
		const void render();

		const GameObject* addGameObject(std::unique_ptr<GameObject> gameObj)
		{
			//if (hasGameObject<T>())  // NoNeed to check gameobejct can be duplicates
			//	return nullptr;

			m_GameObjects.emplace_back(std::move(gameObj));

			return m_GameObjects.back().get();
		}

		template <gameObjectConcept T>
		const bool hasGameObject()
		{
			for (const auto& obj : m_GameObjects)
			{
				if (dynamic_cast<T*>(obj.get()))
					return true;
			}

			return false;
		}

		template <gameObjectConcept T>
		GameObject* getGameObject()
		{
			for (auto& obj : m_GameObjects)
			{
				if (dynamic_cast<T*>(obj.get()))
					return obj.get();
			}

			return nullptr;
		}

		template <gameObjectConcept T>
		void removeGameObject()
		{

		}

		const int getID() { return sceneID; }
	private:
		std::vector<std::unique_ptr<GameObject>> m_GameObjects;
		static int sceneIDCounter;
		int sceneID;
	};
}