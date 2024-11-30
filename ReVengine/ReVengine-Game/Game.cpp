#include "ReVengine.h"
#include "Rev_CoreSystems.h"
#include "Sound/Rev_Sound.H"
#include "GameObjects/GameObject.h"
#include "GameObjects/BaseComponent.h"
#include "GameObjects/Components/CompTransform.h"
#include "GameObjects/Components/CompRender.h"
#include "GameObjects/Components/CompInput.h"
#include "GameObjects/Components/CompCamera.h"
#include "Scenes/Scene.h"
#include "Scenes/SceneManager.h"
#include "Rendering/Texture.h"
#include "GameSettings.h"
#include <glm/vec3.hpp>
#include <SDL_scancode.h>
#include <iostream>

const std::string resourceFolder = "../game_resources";
const std::string doomSprites = "/doomSprites";
const std::string doomEnemies = "/Enemies";
const std::string doomBullets = "/Bullets";

std::unique_ptr<Rev::Scene> Scene1()
{
	//Sound
	{
		const std::string SoundPew = "/sound/pew_pew.wav";

		Rev::Rev_CoreSystems::pRevSound->PlaySound(resourceFolder + SoundPew);
	}

	//Textures
	const std::string mainBulletPath = resourceFolder + doomSprites + doomBullets + "/misla5.png";
	const std::string testDoomFile = resourceFolder + doomSprites + doomEnemies + "/bossb1.png";
	Rev::Texture* testTexture = new Rev::Texture(testDoomFile);
	Rev::Texture* bulletTexture = new Rev::Texture(mainBulletPath);

	//Player
	std::unique_ptr<Rev::GameObject> player = std::make_unique<Rev::GameObject>();
	Rev::CompTransform* transformPlayer = player->addComponent<Rev::CompTransform>(player.get(), glm::vec3{ 0,0,0 });
	Rev::CompCamera* cameraComp = player->addComponent<Rev::CompCamera>(player.get(), transformPlayer);
	Rev::CompInput* inputComp = player->addComponent<Rev::CompInput>(player.get());
	//Input Config
	{
	inputComp->BindAction(SDL_SCANCODE_I, [transformPlayer]() { transformPlayer->AddPitchInput(10); });
	inputComp->BindAction(SDL_SCANCODE_K, [transformPlayer]() { transformPlayer->AddPitchInput(-10); });
	inputComp->BindAction(SDL_SCANCODE_L, [transformPlayer]() { transformPlayer->AddYawInput(10); });
	inputComp->BindAction(SDL_SCANCODE_J, [transformPlayer]() { transformPlayer->AddYawInput(-10); });
	inputComp->BindAction(SDL_SCANCODE_W, [transformPlayer]() { transformPlayer->MoveForward(1); });
	inputComp->BindAction(SDL_SCANCODE_S, [transformPlayer]() { transformPlayer->MoveForward(-1); });
	inputComp->BindAction(SDL_SCANCODE_D, [transformPlayer]() { transformPlayer->MoveRight(1); });
	inputComp->BindAction(SDL_SCANCODE_A, [transformPlayer]() { transformPlayer->MoveRight(-1); });
	}

	//Enemies
	std::unique_ptr<Rev::GameObject> enemy1 = std::make_unique<Rev::GameObject>();
	Rev::CompTransform* transformEnemy1 = enemy1->addComponent<Rev::CompTransform>(enemy1.get(), glm::vec3{ -0, 0, 5 });
	enemy1->addComponent<Rev::CompRender>(enemy1.get(), transformEnemy1, cameraComp, testTexture);
	std::unique_ptr<Rev::GameObject> enemy2 = std::make_unique<Rev::GameObject>();
	Rev::CompTransform* transformEnemy2 = enemy2->addComponent<Rev::CompTransform>(enemy2.get(), glm::vec3{ 1, 0, 5 });
	enemy2->addComponent<Rev::CompRender>(enemy2.get(), transformEnemy2, cameraComp, testTexture);

	//Bullet
	std::unique_ptr<Rev::GameObject> bullet = std::make_unique<Rev::GameObject>();
	Rev::CompTransform* transformBullet = bullet->addComponent<Rev::CompTransform>(bullet.get());
	bullet->addComponent<Rev::CompRender>(bullet.get(), transformBullet, cameraComp, bulletTexture);

	//Scene add gameobects & return
	{
		std::unique_ptr<Rev::Scene> scene = std::make_unique<Rev::Scene>();
		scene->addGameObject(std::move(player));
		scene->addGameObject(std::move(enemy1));
		scene->addGameObject(std::move(enemy2));
		scene->addGameObject(std::move(bullet));
		scene->DisplaySceneHierarchy();
		return std::move(scene);
	}
}

std::unique_ptr<Rev::SceneManager> Load()
{
	std::unique_ptr<Rev::Scene> scene(Scene1());

	std::unique_ptr<Rev::SceneManager> sceneMan = std::make_unique<Rev::SceneManager>();
	sceneMan->addScene(std::move(scene));
	return std::move(sceneMan);
}

int main(int argc, char* argv[])
{
	std::unique_ptr<Rev::ReVengine> pReVengine;
	pReVengine = std::make_unique<Rev::ReVengine>(GameSettings::windowWidth, GameSettings::windowHeight);

	pReVengine->Run(Load);

	return 0;
}