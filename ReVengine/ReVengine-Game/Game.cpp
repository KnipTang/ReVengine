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
#include "Rendering/Shaders/TextureShader.h"
#include "Rendering/Shaders/TextureShader2D.h"

const std::string resourceFolder = "../game_resources";
const std::string doomSprites = "/doomSprites";
const std::string doomEnemies = "/Enemies";
const std::string doomBullets = "/Bullets";
const std::string doomWeapons = "/Weapons";

std::unique_ptr<Rev::Scene> Scene1()
{
	RevDev::RenderWindow* renderer = Rev::Rev_CoreSystems::pRevRender.get();

	//Sound
	{
		const std::string SoundPew = "/sound/pew_pew.wav";

		Rev::Rev_CoreSystems::pRevSound->LoadSound("pew", resourceFolder + SoundPew);
		Rev::Rev_CoreSystems::pRevSound->PlayRevSound("pew");
	}

	//Textures
	const std::string mainBulletPath = resourceFolder + doomSprites + doomBullets + "/misla5.png";
	const std::string secondBulletPath = resourceFolder + doomSprites + doomBullets + "/misla1.png";
	const std::string weaponBulletPath = resourceFolder + doomSprites + doomWeapons + "/pisga0.png";
	const std::string testDoomFile = resourceFolder + doomSprites + doomEnemies + "/bossb1.png";
	Rev::Texture* testTexture = Rev::Rev_CoreSystems::pResourceManager->LoadResource(renderer->GetDevice(),  "TestTexture", testDoomFile);
	Rev::Texture* bulletTexture = Rev::Rev_CoreSystems::pResourceManager->LoadResource(renderer->GetDevice(), "bulletTexture", mainBulletPath);
	Rev::Texture* bullet2Texture = Rev::Rev_CoreSystems::pResourceManager->LoadResource(renderer->GetDevice(), "bullet2Texture", secondBulletPath);
	Rev::Texture* weaponTexture = Rev::Rev_CoreSystems::pResourceManager->LoadResource(renderer->GetDevice(), "weaponTexture", weaponBulletPath);

	Rev::TextureShader* textureShader = new Rev::TextureShader{ renderer->GetDevice(), renderer->GetDeviceContext()};
	Rev::TextureShader2D* textureShader2D = new Rev::TextureShader2D{ renderer->GetDevice(), renderer->GetDeviceContext() };
	//Player
	std::unique_ptr<Rev::GameObject> player = std::make_unique<Rev::GameObject>();
	Rev::CompCamera* cameraComp = player->addComponent<Rev::CompCamera>(player.get(), player->transform);
	Rev::CompInput* inputComp = player->addComponent<Rev::CompInput>(player.get());
	//Gun
	std::unique_ptr<Rev::GameObject> gun = std::make_unique<Rev::GameObject>();
	gun->transform->SetPosition(0, -0.5f, 0);
	gun->addComponent<Rev::CompRender>(gun.get(), gun->transform, cameraComp, textureShader2D, weaponTexture, 0.3f, 0.3f);

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
	enemy1->addComponent<Rev::CompRender>(enemy1.get(), enemy1->transform, cameraComp, textureShader, testTexture);
	std::unique_ptr<Rev::GameObject> enemy2 = std::make_unique<Rev::GameObject>();
	enemy2->transform->SetPosition(1, 0, 5);
	enemy2->addComponent<Rev::CompRender>(enemy2.get(), enemy2->transform, cameraComp, textureShader, testTexture);

	//Bullet
	std::unique_ptr<Rev::GameObject> bullet = std::make_unique<Rev::GameObject>();
	bullet->addComponent<Rev::CompRender>(bullet.get(), bullet->transform, cameraComp, textureShader, bulletTexture);
	bullet->addComponent<BulletComp>(bullet.get(), bullet->transform);

	std::unique_ptr<Rev::GameObject> grandParent = std::make_unique<Rev::GameObject>();
	grandParent->transform->SetPosition(3, 0, 0);
	grandParent->addComponent<Rev::CompRender>(grandParent.get(), grandParent->transform, cameraComp, textureShader, bullet2Texture);
	Rev::GameObject* parent = new Rev::GameObject;
	parent->transform->SetPosition(4, 0, 0);
	parent->addComponent<Rev::CompRender>(parent, parent->transform, cameraComp, textureShader, bulletTexture);
	Rev::GameObject* son = new Rev::GameObject;
	son->transform->SetPosition(8, 1, 0);
	son->addComponent<Rev::CompRender>(son, son->transform, cameraComp, textureShader, bulletTexture);
	grandParent->AddChild(parent);
	parent->AddChild(son);

	Rev::CompTransform* grandTransform = grandParent->transform;
	inputComp->BindAction(SDL_SCANCODE_T, [grandTransform]() { grandTransform->MoveRight(1); });
	Rev::CompTransform* parentTransform = parent->transform;
	inputComp->BindAction(SDL_SCANCODE_G, [parentTransform]() { parentTransform->AddYawInput(0.1); });
	Rev::CompTransform* childTransform = son->transform;
	inputComp->BindAction(SDL_SCANCODE_B, [childTransform]() { childTransform->AddYawInput(0.1); });

	//Scene add gameobects & return
	{
		std::unique_ptr<Rev::Scene> scene = std::make_unique<Rev::Scene>();
		scene->addGameObject(std::move(player));
		scene->addGameObject(std::move(enemy1));
		scene->addGameObject(std::move(enemy2));
		scene->addGameObject(std::move(gun));
		scene->addGameObject(std::move(grandParent));
		scene->DisplaySceneHierarchy();
		return std::move(scene);
	}
}

Rev::SceneManager* Load()
{
	std::unique_ptr<Rev::Scene> scene(Scene1());

	Rev::Rev_CoreSystems::pSceneManager->addScene(std::move(scene));
	return Rev::Rev_CoreSystems::pSceneManager.get();
}

int main(int argc, char* argv[])
{
	std::unique_ptr<Rev::ReVengine> pReVengine;
	pReVengine = std::make_unique<Rev::ReVengine>(GameSettings::windowWidth, GameSettings::windowHeight);

	pReVengine->Run(Load);

	return 0;
}