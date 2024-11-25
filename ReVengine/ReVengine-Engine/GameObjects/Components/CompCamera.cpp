#include "CompCamera.h"
#include "Rendering/Camera/Camera.h"
#include <Utils/MousePos.h>
#include <Rev_CoreSystems.h>
#include "GameObjects/Components/CompTransform.h"

using namespace Rev;

CompCamera::CompCamera(GameObject* gameObj, Rev::CompTransform* transform, bool flipControlls) :
	BaseComponent(gameObj),
	m_Camera{ std::make_unique<RevDev::Camera>() },
	m_Transform{ transform },
	m_LookSensitivity{0.1f},
	m_ControllsFlipped{flipControlls}
{

}

void Rev::CompCamera::update()
{
	m_Camera->Update(m_Transform->GetPosition(), m_Transform->GetRotation());

	MouseRelativeMotion delta = Rev::Rev_CoreSystems::pInputManager->GetMouseRelativeMotion();

	std::pair<float, float> turnValue = { (float)delta.x * m_LookSensitivity, (float)delta.y * m_LookSensitivity };

	if(m_ControllsFlipped)
		Turn(turnValue.first, turnValue.second);
	else
		Turn(turnValue.second, turnValue.first);
}

void Rev::CompCamera::Turn(float x, float y)
{
	m_Transform->Turn(x, y);
}