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
#include "Objects/Weapons/BulletComp.h"

const std::string resourceFolder = "../game_resources";
const std::string doomSprites = "/doomSprites";
const std::string doomEnemies = "/Enemies";
const std::string doomBullets = "/Bullets";
const std::string doomWeapons = "/Weapons";

std::unique_ptr<Rev::Scene> Scene1()
{
	//Sound
	{
		const std::string SoundPew = "/sound/pew_pew.wav";

		Rev::Rev_CoreSystems::pRevSound->PlaySound(resourceFolder + SoundPew);
	}

	//Textures
	const std::string mainBulletPath = resourceFolder + doomSprites + doomBullets + "/misla5.png";
	const std::string secondBulletPath = resourceFolder + doomSprites + doomBullets + "/misla1.png";
	const std::string weaponBulletPath = resourceFolder + doomSprites + doomWeapons + "/pisga0.png";
	const std::string testDoomFile = resourceFolder + doomSprites + doomEnemies + "/bossb1.png";
	Rev::Texture* testTexture = new Rev::Texture(testDoomFile);
	Rev::Texture* bulletTexture = new Rev::Texture(mainBulletPath);
	Rev::Texture* bullet2Texture = new Rev::Texture(secondBulletPath);
	Rev::Texture* weaponTexture = new Rev::Texture(weaponBulletPath);

	//Player
	std::unique_ptr<Rev::GameObject> player = std::make_unique<Rev::GameObject>();
	Rev::CompCamera* cameraComp = player->addComponent<Rev::CompCamera>(player.get(), player->transform);
	Rev::CompInput* inputComp = player->addComponent<Rev::CompInput>(player.get());
	//Gun
	Rev::GameObject* gun = new Rev::GameObject{};
	gun->transform->SetPosition(0, 0, 1);
	gun->addComponent<Rev::CompRender>(gun, gun->transform, cameraComp, weaponTexture, 0.3f, 0.3f);
	player->AddChild(gun);

	//Input Config
	{
	Rev::CompTransform* playerTransform = player->transform;
	inputComp->BindAction(SDL_SCANCODE_I, [playerTransform]() { playerTransform->AddPitchInput(10); });
	inputComp->BindAction(SDL_SCANCODE_K, [playerTransform]() { playerTransform->AddPitchInput(-10); });
	inputComp->BindAction(SDL_SCANCODE_L, [playerTransform]() { playerTransform->AddYawInput(10); });
	inputComp->BindAction(SDL_SCANCODE_J, [playerTransform]() { playerTransform->AddYawInput(-10); });
	inputComp->BindAction(SDL_SCANCODE_W, [playerTransform]() { playerTransform->MoveForward(1); });
	inputComp->BindAction(SDL_SCANCODE_S, [playerTransform]() { playerTransform->MoveForward(-1); });
	inputComp->BindAction(SDL_SCANCODE_D, [playerTransform]() { playerTransform->MoveRight(1); });
	inputComp->BindAction(SDL_SCANCODE_A, [playerTransform]() { playerTransform->MoveRight(-1); });
	}

	//Enemies
	std::unique_ptr<Rev::GameObject> enemy1 = std::make_unique<Rev::GameObject>();
	enemy1->transform->SetPosition(0, 0, 5);
	enemy1->addComponent<Rev::CompRender>(enemy1.get(), enemy1->transform, cameraComp, testTexture);
	std::unique_ptr<Rev::GameObject> enemy2 = std::make_unique<Rev::GameObject>();
	enemy2->transform->SetPosition(1, 0, 5);
	enemy2->addComponent<Rev::CompRender>(enemy2.get(), enemy2->transform, cameraComp, testTexture);

	//Bullet
	std::unique_ptr<Rev::GameObject> bullet = std::make_unique<Rev::GameObject>();
	bullet->addComponent<Rev::CompRender>(bullet.get(), bullet->transform, cameraComp, bulletTexture);
	bullet->addComponent<BulletComp>(bullet.get(), bullet->transform);

	std::unique_ptr<Rev::GameObject> grandParent = std::make_unique<Rev::GameObject>();
	grandParent->transform->SetPosition(3, 0, 0);
	grandParent->addComponent<Rev::CompRender>(grandParent.get(), grandParent->transform, cameraComp, bullet2Texture);
	Rev::GameObject* parent = new Rev::GameObject;
	parent->transform->SetPosition(4, 0, 0);
	parent->addComponent<Rev::CompRender>(parent, parent->transform, cameraComp, bulletTexture);
	Rev::GameObject* son = new Rev::GameObject;
	son->transform->SetPosition(8, 1, 0);
	son->addComponent<Rev::CompRender>(son, son->transform, cameraComp, bulletTexture);
	grandParent->AddChild(parent);
	parent->AddChild(son);

	Rev::CompTransform* grandTransform = grandParent->transform;
	inputComp->BindAction(SDL_SCANCODE_T, [grandTransform]() { grandTransform->MoveRight(1); });
	Rev::CompTransform* parentTransform = parent->transform;
	inputComp->BindAction(SDL_SCANCODE_G, [parentTransform]() { parentTransform->MoveRight(1); });
	Rev::CompTransform* childTransform = son->transform;
	inputComp->BindAction(SDL_SCANCODE_B, [childTransform]() { childTransform->MoveRight(1); });

	//Scene add gameobects & return
	{
		std::unique_ptr<Rev::Scene> scene = std::make_unique<Rev::Scene>();
		scene->addGameObject(std::move(player));
		scene->addGameObject(std::move(enemy1));
		scene->addGameObject(std::move(enemy2));
		//scene->addGameObject(std::move(bullet));
		scene->addGameObject(std::move(grandParent));
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