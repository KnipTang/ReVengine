#pragma once

#include <vector>
#include <memory>

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

		const GameObject* addGameObject(std::unique_ptr<GameObject> gameObj);

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
		T* getGameObject()
		{
			for (auto& obj : m_GameObjects)
			{
				if (auto derivedComp = dynamic_cast<T*>(obj.get()))
					return derivedComp;
			}

			return nullptr;
		}

		template <gameObjectConcept T>
		void removeGameObject()
		{
			m_GameObjects.erase(
				std::remove_if(m_GameObjects.begin(), m_GameObjects.end(),
					[](const std::unique_ptr<GameObject>& obj) {
						return dynamic_cast<T*>(obj.get()) != nullptr;
					}),
				m_GameObjects.end());
		}

		const int getID() { return sceneID; }
	private:
		std::vector<std::unique_ptr<GameObject>> m_GameObjects;
		static int sceneIDCounter;
		int sceneID;
	};
}