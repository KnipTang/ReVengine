#include <SDL.h>

#include "ReVengine.h"
#include "Rev_CoreSystems.h"
#include "Sound/Rev_Sound.H"
#include "GameObjects/GameObject.h"
#include "GameObjects/BaseComponent.h"
#include "GameObjects/Components/CompTest.h"
#include "GameObjects/Components/CompTransform.h"
#include "GameObjects/Components/CompRender.h"
#include "Scenes/Scene.h"
#include "Scenes/SceneManager.h"

#include <iostream>

std::unique_ptr<Rev::SceneManager> Load()
{
	const std::string resourceFolder = "../game_resources";
	const std::string soundFolder = "/sound";
	const std::string sound_pewpew = "/pew_pew.wav";

	Rev::Rev_CoreSystems::pRevSound->PlaySound(resourceFolder + soundFolder + sound_pewpew);

	std::unique_ptr<Rev::GameObject> player = std::make_unique<Rev::GameObject>();
	std::unique_ptr<Rev::GameObject> player1 = std::make_unique<Rev::GameObject>();

	std::string vertexFile = "../DirectX11/shaders/VertexShader.cso";
	std::string pixelFile = "../DirectX11/shaders/PixelShader.cso";

	/*
	const std::vector<Vertex> vertices
	{
		{ {-1.0f,  -1.f,  -1.0f }, { 1.0f, 0.0f, 0.0f } },
		{ { 1.f, -1.f,  -1.0f }, { 0.0f, 1.0f, 0.0f } },
		{ {-1.0f, 1.f,  -1.0f }, { 0.0f, 0.0f, 1.0f } },
		{ {1.0f, 1.f,  -1.0f }, { 0.0f, 0.0f, 1.0f } },
		{ {-1.0f, -1.f,  1.0f }, { 0.0f, 0.0f, 1.0f } },
		{ {1.0f, -1.f,  1.0f }, { 0.0f, 0.0f, 1.0f } },
		{ {-1.0f, 1.f,  1.0f }, { 0.0f, 0.0f, 1.0f } },
		{ {1.0f, 1.f,  1.0f }, { 0.0f, 0.0f, 1.0f } },
	};

	std::vector<unsigned short> indices =
	{
		0,2,1, 2,3,1,
		1,3,5, 3,7,5,
		2,6,3, 3,6,7,
		4,5,7, 4,7,6,
		0,4,2, 2,4,6,
		0,1,4, 1,5,4,
	};
	*/

	player->addComponent<Rev::CompTransform>(player.get(), Vector3{5,8,2});
	player->addComponent<Rev::CompTest>(player.get());
	player->addComponent<Rev::CompRender>(player.get());
	player->hasComponent<Rev::CompTest>();
	player->removeComponent<Rev::CompTransform>();
	Rev::CompTest* tt = player->getComponent<Rev::CompTest>();

	std::unique_ptr<Rev::Scene> tempScene = std::make_unique<Rev::Scene>();
	tempScene->addGameObject(std::move(player));

	std::unique_ptr<Rev::SceneManager> tempSceneMan = std::make_unique<Rev::SceneManager>();
	tempSceneMan->addScene(std::move(tempScene));

	return std::move(tempSceneMan);
}

int main(int argc, char* argv[])
{
	int windowWidth = 700;
	int windowHeight = 500;

	std::unique_ptr<Rev::ReVengine> pReVengine;
	pReVengine = std::make_unique<Rev::ReVengine>(windowWidth, windowHeight);

	pReVengine->Run(Load);

	return 0;
}