#include "CompCamera.h"
#include "Rendering/Camera/Camera.h"

using namespace Rev;

CompCamera::CompCamera(GameObject* gameObj) :
	BaseComponent(gameObj),
	m_Camera{ std::make_unique<RevDev::Camera>() }
{

}

void Rev::CompCamera::update()
{
	m_Camera->Update();
}

void Rev::CompCamera::AddYawInput(float input)
{
	m_Camera->AddYawInput(input);
}

void Rev::CompCamera::AddPitchInput(float input)
{
	m_Camera->AddPitchInput(input);
}