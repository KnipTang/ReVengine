#include "CompRender.h"
#include "Rev_CoreSystems.h"
#include "CompTransform.h"
#include "CompCamera.h"
#include "Rendering/Texture.h"

using namespace Rev;

CompRender::CompRender(GameObject* gameObj, CompTransform* transform, CompCamera* camera, Texture* texture, int width, int height) :
	BaseComponent(gameObj),
	m_TransformComp{ transform },
	m_CameraComp{ camera },
	m_MeshId{}
{
	Vector3 pos = m_TransformComp->getPosition();
	m_Vertices =
	{
		//Bottom Left
		{ { pos.x - width,  pos.y - height, pos.z }, { 0.f, 1.f } },
		//Bottom Right
		{ { pos.x + width,  pos.y - height, pos.z }, { 1.f, 1.f } },
		//Top Left
		{ { pos.x - width,  pos.y + height, pos.z }, { 0.f, 0.f } },
		//Top Right
		{ { pos.x + width,  pos.y + height, pos.z }, { 1.f, 0.f } },
	};

	m_Indices =
	{
		0, 1, 2,
		2 ,1, 3,
	};

	m_MeshId = Rev_CoreSystems::pRevRender->AddMesh(m_Vertices, m_Indices, texture);
}

const void CompRender::render()
{
	Rev_CoreSystems::pRevRender->DrawMesh(m_MeshId, m_CameraComp->GetCamera()->GetViewMatrix());
}
