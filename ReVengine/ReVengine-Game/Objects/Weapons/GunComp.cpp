#include "GunComp.h"
#include "GameObjects/GameObject.h"
#include "Scenes/Scene.h"
#include "Rev_CoreSystems.h"
#include "GameObjects/Components/CompTransform.h"
#include "GameObjects/Components/CompTransform.h"

GunComp::GunComp(Rev::GameObject* gameObj, Rev::CompTransform* playerTransform, std::function<Rev::GameObject* ()> bulletFunc) :
	Rev::BaseComponent(gameObj),
	m_PlayerTransform{ playerTransform },
	m_BulletFunc{ bulletFunc }
{

}

GunComp::~GunComp()
{

}

void GunComp::Fire()
{
	Rev::GameObject* bullet = m_BulletFunc();
	bullet->transform->SetPosition(m_PlayerTransform->GetPosition());
	Rev::Rev_CoreSystems::pSceneManager->GetActiveScenes().at(0)->addGameObject(bullet);
}