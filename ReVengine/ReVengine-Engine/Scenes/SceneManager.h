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

		void update();
		void fixedUpdate();
		const void render();

		const Scene* addScene(std::unique_ptr<Scene> scene);

		template <sceneConcept T>
		Scene* getScene()
		{
			for (auto& scene : m_Scenes)
			{
				if (dynamic_cast<T*>(scene.get()))
					return scene.get();
			}

			return nullptr;
		}

		template <sceneConcept T>
		void removeScene()
		{

		}

		const int getID() { return sceneManagerID; }
	private:
		std::vector<std::unique_ptr<Scene>> m_Scenes;
		static int sceneManagerIDCounter;
		int sceneManagerID;
	};
}