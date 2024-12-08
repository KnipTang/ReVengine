#include "CompRender.h"
#include "Rev_CoreSystems.h"
#include "CompTransform.h"
#include "CompCamera.h"
#include "Rendering/Texture.h"
#include "glm/vec3.hpp"
#include <iostream>

using namespace Rev;

CompRender::CompRender(GameObject* gameObj, CompTransform* transform, CompCamera* camera, Texture* texture, float widthTexture, float heightTexture) :
	BaseComponent(gameObj),
	m_TransformComp{ transform },
	m_CameraComp{ camera },
	m_MeshId{}
{
	float depthZ = m_TransformComp->GetPosition().z;
	m_Vertices =
	{
		//Bottom Left
		{ { 0 - widthTexture / 2,  0 - heightTexture / 2, depthZ }, { 0.f, 1.f } },
		//Bottom Right
		{ { 0 + widthTexture / 2,  0 - heightTexture / 2, depthZ }, { 1.f, 1.f } },
		//Top Left
		{ { 0 - widthTexture / 2,  0 + heightTexture / 2, depthZ }, { 0.f, 0.f } },
		//Top Right
		{ { 0 + widthTexture / 2,  0 + heightTexture / 2, depthZ }, { 1.f, 0.f } },
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
	Rev_CoreSystems::pRevRender->DrawMesh(m_MeshId, m_TransformComp->GetModelMatrix(), m_CameraComp->GetCamera()->GetViewMatrix());
}
