#include "CompCamera.h"
#include "Rendering/Camera/Camera.h"
#include <Utils/MousePos.h>
#include <Rev_CoreSystems.h>
#include "GameSettings.h"

using namespace Rev;

CompCamera::CompCamera(GameObject* gameObj) :
	BaseComponent(gameObj),
	m_Camera{ std::make_unique<RevDev::Camera>() },
	m_LookSensitivity{5.f}
{

}

void Rev::CompCamera::update()
{
	m_Camera->Update();

	MouseRelativeMotion delta = Rev::Rev_CoreSystems::pInputManager->GetMouseRelativeMotion();
	
	//int deltaX = delta.x - (GameSettings::windowWidth / 2);
	//int deltaY = delta.y - (GameSettings::windowHeight / 2);
	
	Turn((float)delta.x, (float)delta.y);
}

void Rev::CompCamera::Turn(float x, float y)
{
	x = x / m_LookSensitivity;
	y = y / m_LookSensitivity;

	m_Camera->AddYawInput(x);
	m_Camera->AddPitchInput(y);
}

void Rev::CompCamera::AddYawInput(float input)
{
	m_Camera->AddYawInput(input);
}

void Rev::CompCamera::AddPitchInput(float input)
{
	m_Camera->AddPitchInput(input);
}