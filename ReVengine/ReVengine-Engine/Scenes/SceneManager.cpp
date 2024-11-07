#include "SceneManager.h"
#include "Scenes/Scene.h"

using namespace Rev;

int SceneManager::sceneManagerIDCounter = 0;

SceneManager::SceneManager() :
	sceneManagerID{ sceneManagerIDCounter++ }
{
}

SceneManager::~SceneManager()
{
}

void SceneManager::update()
{
	for (auto& scene : m_Scenes)
	{
		scene->update();
	}
}

void SceneManager::fixedUpdate()
{
	for (auto& scene : m_Scenes)
	{
		scene->fixedUpdate();
	}
}

const void SceneManager::render()
{
	for (auto& scene : m_Scenes)
	{
		scene->render();
	}
}

const Scene* SceneManager::addScene(std::unique_ptr<Scene> scene)
{
	m_Scenes.emplace_back(std::move(scene));

	return m_Scenes.back().get();
}