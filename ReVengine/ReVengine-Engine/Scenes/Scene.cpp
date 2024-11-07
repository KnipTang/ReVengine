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

void Scene::update()
{
	for (auto& obj : m_GameObjects)
	{
		obj->update();
	}
}

void Scene::fixedUpdate()
{
	for (auto& obj : m_GameObjects)
	{
		obj->fixedUpdate();
	}
}

const void Scene::render()
{
	for (auto& obj : m_GameObjects)
	{
		obj->render();
	}
}

const GameObject* Scene::addGameObject(std::unique_ptr<GameObject> gameObj)
{
	//if (hasGameObject<T>())  // NoNeed to check gameobejct can be duplicates
	//	return nullptr;

	m_GameObjects.emplace_back(std::move(gameObj));

	return m_GameObjects.back().get();
}