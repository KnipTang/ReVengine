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
	


	player->addComponent<Rev::CompTransform>(player.get(), Vector3{-2,0,-5});
	player->addComponent<Rev::CompRender>(player.get(), player->getComponent<Rev::CompTransform>(), 1);
	player1->addComponent<Rev::CompTransform>(player1.get(), Vector3{ 2,0,-5 });
	player1->addComponent<Rev::CompRender>(player1.get(), player1->getComponent<Rev::CompTransform>(), 0);

	std::unique_ptr<Rev::Scene> tempScene = std::make_unique<Rev::Scene>();
	tempScene->addGameObject(std::move(player));
	tempScene->addGameObject(std::move(player1));

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