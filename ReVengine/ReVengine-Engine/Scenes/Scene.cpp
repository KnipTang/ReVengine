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