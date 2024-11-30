#include "Scene.h"
#include "GameObjects/GameObject.h"

using namespace Rev;

int Scene::sceneIDCounter = 0;

Scene::Scene() :
	sceneID{ sceneIDCounter++ }
{
}

Scene::~Scene()
{
}

void Scene::update(float deltaTime)
{
	for (auto&& obj : m_GameObjects)
	{
		if(obj->m_Enabled) obj->update(deltaTime);
	}
}

void Scene::fixedUpdate(float fixedDeltaTime)
{
	for (auto&& obj : m_GameObjects)
	{
		if (obj->m_Enabled) obj->fixedUpdate(fixedDeltaTime);
	}
}

const void Scene::render()
{
	for (auto&& obj : m_GameObjects)
	{
		if (obj->m_Enabled) obj->render();
	}
}

const GameObject* Scene::addGameObject(std::unique_ptr<GameObject> gameObj)
{
	//if (hasGameObject<T>())  // NoNeed to check gameobejct can be duplicates
	//	return nullptr;

	m_GameObjects.emplace_back(std::move(gameObj));

	return m_GameObjects.back().get();
}