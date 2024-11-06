#include <SDL.h>

#include "ReVengine.h"
#include "Rev_CoreSystems.h"
#include "Sound/Rev_Sound.H"
#include "GameObjects/GameObject.h"
#include "GameObjects/BaseComponent.h"
#include "GameObjects/Components/CompTest.h"
#include "GameObjects/Components/CompTransform.h"
#include "Scenes/Scene.h"

void Load()
{
	const std::string resourceFolder = "../game_resources";
	const std::string soundFolder = "/sound";
	const std::string sound_pewpew = "/pew_pew.wav";

	Rev::Rev_CoreSystems::pRevSound->PlaySound(resourceFolder + soundFolder + sound_pewpew);

	std::unique_ptr<Rev::GameObject> player = std::make_unique<Rev::GameObject>();
	std::unique_ptr<Rev::GameObject> player1 = std::make_unique<Rev::GameObject>();

	player->addComponent<Rev::CompTransform>(player.get());
	player->addComponent<Rev::CompTest>(player.get());
	player->hasComponent<Rev::CompTest>();
	player->removeComponent<Rev::CompTest>();
	player->getComponent<Rev::CompTest>();

	Rev::Scene* tempScene = new Rev::Scene{};
	tempScene->addGameObject(std::move(player));
	tempScene->update();
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