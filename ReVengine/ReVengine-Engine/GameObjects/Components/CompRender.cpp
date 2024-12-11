#include "CompRender.h"
#include "Rev_CoreSystems.h"
#include "CompTransform.h"
#include "CompCamera.h"
#include "Rendering/Shaders/TextureShader.h"
#include "Rendering/Texture.h"
#include "glm/vec3.hpp"
#include "DirectXMath.h"

using namespace Rev;

CompRender::CompRender(GameObject* gameObj, CompTransform* transform, CompCamera* camera, BaseShader* shader, Texture* texture, float widthTexture, float heightTexture) :
	BaseComponent(gameObj),
	m_TransformComp{ transform },
	m_CameraComp{ camera },
	m_Shader{ shader },
	m_Texture{ texture },
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

	m_MeshId = Rev_CoreSystems::pRevRender->AddMesh(m_Vertices, m_Indices);
}

const void CompRender::render()
{
	DirectX::XMMATRIX modelMatrix = DirectX::XMLoadFloat4x4(reinterpret_cast<const DirectX::XMFLOAT4X4*>(&m_TransformComp->GetModelMatrix()));
	m_Shader->SetShader(modelMatrix, m_CameraComp->GetCamera()->GetViewMatrix(), Rev::Rev_CoreSystems::pRevRender->getProjectionMatrix(),
		m_Texture->GetShaderResourceView());
	m_Shader->SetShaderStages();
	Rev_CoreSystems::pRevRender->DrawMesh(m_MeshId);
}
