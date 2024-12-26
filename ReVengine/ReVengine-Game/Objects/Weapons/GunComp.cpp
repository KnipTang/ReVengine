#include "GunComp.h"
#include "GameObjects/GameObject.h"
#include "Scenes/Scene.h"
#include "Rev_CoreSystems.h"
#include "GameObjects/Components/CompTransform.h"

GunComp::GunComp(Rev::GameObject* gameObj, Rev::GameObject* bullet) :
	Rev::BaseComponent(gameObj),
	m_Bullet{ bullet }
{

}

GunComp::~GunComp()
{
}

void GunComp::Fire()
{
	Rev::GameObject* bullet = new Rev::GameObject{ *m_Bullet };
	bullet->transform->SetPosition(m_GameObject->transform->GetPosition());
	Rev::Rev_CoreSystems::pSceneManager->GetActiveScenes().at(0)->addGameObject(bullet);
	Rev::Rev_CoreSystems::pSceneManager->GetActiveScenes().at(0)->DisplaySceneHierarchy();
}