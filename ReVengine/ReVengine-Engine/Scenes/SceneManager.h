#pragma once

#include <vector>
#include <memory>

namespace Rev
{
	class Scene;
}

namespace Rev
{
	template <class T>
	concept sceneConcept = std::derived_from<T, Scene>;

	class SceneManager
	{
	public:
		SceneManager();
		~SceneManager();

		void update(float deltaTime);
		void lateUpdate(float deltaTime);
		void fixedUpdate(float fixedDeltaTime);
		const void render();

		const Scene* addScene(std::unique_ptr<Scene> scene);

		template <sceneConcept T>
		T* getScene()
		{
			for (auto& scene : m_Scenes)
			{
				if (auto derivedComp = dynamic_cast<T*>(scene.get()))
					return derivedComp;
			}

			return nullptr;
		}

		template <sceneConcept T>
		void removeScene()
		{
			m_Scenes.erase(
				std::remove_if(m_Scenes.begin(), m_Scenes.end(),
					[](const std::unique_ptr<Scene>& scene) {
						return dynamic_cast<T*>(scene.get()) != nullptr;
					}),
				m_Scenes.end());
		}

		const int GetID() { return sceneManagerID; }
	private:
		std::vector<std::unique_ptr<Scene>> m_Scenes;
		static int sceneManagerIDCounter;
		int sceneManagerID;
	};
}