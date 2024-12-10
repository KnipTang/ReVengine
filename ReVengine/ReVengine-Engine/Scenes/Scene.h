#pragma once

#include <vector>
#include <memory>
#include <algorithm>
#include "GameObjects/GameObject.h"

namespace Rev
{
	template <class T>
	concept gameObjectConcept = std::derived_from<T, GameObject>;

	class Scene
	{
	public:
		Scene();
		~Scene();

		void update(float deltaTime);
		void lateUpdate(float deltaTime);
		void fixedUpdate(float fixedDeltaTime);
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

		void DisplaySceneHierarchy()
		{
			std::printf("Scene Hierachy: %s\tSceneID: %i\n", typeid(*this).name(), sceneID);
			std::ranges::for_each(m_GameObjects,
				[](std::unique_ptr<GameObject>& obj) -> void
				{
					obj->DisplayHierarchy();
				}
			);
		}

		const int GetID() { return sceneID; }
	private:
		std::vector<std::unique_ptr<GameObject>> m_GameObjects;
		static int sceneIDCounter;
		int sceneID;
	};
}