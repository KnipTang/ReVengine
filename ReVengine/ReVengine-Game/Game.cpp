#include "ReVengine.h"
#include "Rev_CoreSystems.h"
#include "Sound/Rev_Sound.H"
#include "GameObjects/GameObject.h"
#include "GameObjects/BaseComponent.h"
#include "GameObjects/Components/CompTransform.h"
#include "GameObjects/Components/CompRender.h"
#include "GameObjects/Components/CompInput.h"
#include "GameObjects/Components/CompCamera.h"
#include "GameObjects/Components/CompCollision.h"
#include "Scenes/Scene.h"
#include "Scenes/SceneManager.h"
#include "Rendering/Texture.h"
#include "GameSettings.h"
#include <glm/vec3.hpp>
#include <SDL_scancode.h>
#include <iostream>
#include "Objects/Weapons/BulletComp.h"
#include "Objects/Weapons/GunComp.h"
#include "Objects/Enemies/LookAtPlayerComp.h"
#include "Rendering/Shaders/TextureShader.h"
#include "Rendering/Shaders/TextureShader2D.h"
#include "Physics/Physics.h"

const std::string resourceFolder = "../game_resources";
const std::string doomSprites = "/doomSprites";
const std::string doomEnemies = "/Enemies";
const std::string doomBullets = "/Bullets";
const std::string doomWeapons = "/Weapons";
const std::string doomMap = "/Map";


std::unique_ptr<Rev::Scene> Scene1()
{
	std::unique_ptr<Rev::Scene> scene = std::make_unique<Rev::Scene>();
	Rev::Physics* physicsHandle = scene->getPhysicsHandle();
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
	const std::string doomFloor = resourceFolder + doomSprites + doomMap + "/floor0_5.png";
	Rev::Texture* testTexture = Rev::Rev_CoreSystems::pResourceManager->LoadResource(renderer->GetDevice(),  "TestTexture", testDoomFile);
	Rev::Texture* bulletTexture = Rev::Rev_CoreSystems::pResourceManager->LoadResource(renderer->GetDevice(), "bulletTexture", mainBulletPath);
	Rev::Texture* bullet2Texture = Rev::Rev_CoreSystems::pResourceManager->LoadResource(renderer->GetDevice(), "bullet2Texture", secondBulletPath);
	Rev::Texture* weaponTexture = Rev::Rev_CoreSystems::pResourceManager->LoadResource(renderer->GetDevice(), "weaponTexture", weaponBulletPath);
	Rev::Texture* floorTexture = Rev::Rev_CoreSystems::pResourceManager->LoadResource(renderer->GetDevice(), "floor", doomFloor);

	Rev::TextureShader* textureShader = new Rev::TextureShader{ renderer->GetDevice(), renderer->GetDeviceContext()};
	Rev::TextureShader2D* textureShader2D = new Rev::TextureShader2D{ renderer->GetDevice(), renderer->GetDeviceContext() };

	//Player
	std::unique_ptr<Rev::GameObject> player = std::make_unique<Rev::GameObject>("Player");
	player->transform->SetPosition(0, 0.5f, 0);
	Rev::CompCamera* cameraComp = player->addComponent<Rev::CompCamera>(player.get(), player->transform);
	Rev::CompInput* inputComp = player->addComponent<Rev::CompInput>(player.get());
	player->addComponent<Rev::CompCollision>(player.get(), physicsHandle, false, false, glm::vec3{0.1f, 1, 0.1f});
	cameraComp->LockAxes(RotationAxes::x, true);

	//Map
	std::vector<std::unique_ptr<Rev::GameObject>> floors;
	for (float i = 0; i < 10; i+=0.5f)
	{
		for (float j = 0; j < 10; j += 0.5f)
		{
			floors.emplace_back(std::make_unique<Rev::GameObject>("Floor"));
			auto&& currentFloor = floors.back();

			currentFloor->transform->SetRotationDegree(90, 0, 0);
			currentFloor->transform->SetPosition(i, 0, j);
			currentFloor->addComponent<Rev::CompRender>(currentFloor.get(), currentFloor->transform, cameraComp, textureShader, floorTexture, 1.f, 1.f);

		}
	}

	//Gun
	std::unique_ptr<Rev::GameObject> gun = std::make_unique<Rev::GameObject>("Gun");
	gun->transform->SetPosition(0, -1.f, 0);
	Rev::CompRender* gunRender = gun->addComponent<Rev::CompRender>(gun.get(), gun->transform, cameraComp, textureShader2D, weaponTexture, 0.7f, 0.7f, true);
	gunRender->m_Is2D = true;
	GunComp* gunComp = gun->addComponent<GunComp>(gun.get(), player->transform, 0.25f,
		[cameraComp, textureShader, bulletTexture, physicsHandle]() {
			Rev::GameObject* bullet = new Rev::GameObject{"Bullet"};
			bullet->addComponent<Rev::CompRender>(bullet, bullet->transform, cameraComp, textureShader, bulletTexture, 0.1f, 0.1f, true);
			BulletComp& bulletComp = *bullet->addComponent<BulletComp>(bullet, 50.f);
			bulletComp.SetMaxTravelDistance(100);
			Rev::CompCollision& bulletColl = *bullet->addComponent<Rev::CompCollision>(bullet, physicsHandle, false, false, glm::vec3{ 0.1f, 0.1f, 0.1f });
			bulletColl.SetOnContactFunction(
				[](Rev::CompCollision* other) {
				Rev::GameObject& obj = *other->GetGameObject();
				if (obj.m_Tag != "Bullet" && obj.m_Tag != "Player") obj.Destroy();
				});
			return bullet;
		});
	gunComp->SetFireSoundEffect("pew");

	Rev::CompTransform* playerTransform = player->transform;
	float walkingSpeed = 0.05f;
	//Input Config
	{
	inputComp->BindKeyAction(SDL_SCANCODE_I, [playerTransform]() { playerTransform->AddPitchInput(10); });
	inputComp->BindKeyAction(SDL_SCANCODE_K, [playerTransform]() { playerTransform->AddPitchInput(-10); });
	inputComp->BindKeyAction(SDL_SCANCODE_L, [playerTransform]() { playerTransform->AddYawInput(10); });
	inputComp->BindKeyAction(SDL_SCANCODE_J, [playerTransform]() { playerTransform->AddYawInput(-10); });
	inputComp->BindKeyAction(SDL_SCANCODE_W, [playerTransform, walkingSpeed]() { playerTransform->MoveForward(1, walkingSpeed); });
	inputComp->BindKeyAction(SDL_SCANCODE_S, [playerTransform, walkingSpeed]() { playerTransform->MoveForward(-1, walkingSpeed); });
	inputComp->BindKeyAction(SDL_SCANCODE_D, [playerTransform, walkingSpeed]() { playerTransform->MoveRight(1, walkingSpeed); });
	inputComp->BindKeyAction(SDL_SCANCODE_A, [playerTransform, walkingSpeed]() { playerTransform->MoveRight(-1, walkingSpeed); });

	inputComp->BindKeyAction(SDL_SCANCODE_R, [playerTransform]() { playerTransform->SetRotationRad(0,0,0); });

	inputComp->BindMouseAction(SDL_BUTTON_LEFT, [gunComp]() { gunComp->Fire(); });

	inputComp->BindKeyAction(SDL_SCANCODE_G, [gunComp]() { gunComp->Fire(); });
	}

	auto lambdaCollEnemy = 
		[](Rev::CompCollision* other) {
		Rev::GameObject& obj = *other->GetGameObject();
		if(obj.m_Tag == "Bullet") obj.Destroy();
		};

	//Enemies
	std::unique_ptr<Rev::GameObject> enemy1 = std::make_unique<Rev::GameObject>("Enemy1");
	enemy1->addComponent<LookAtPlayerComp>(enemy1.get(), playerTransform);
	enemy1->transform->SetPosition(0, 0, 5);
	enemy1->addComponent<Rev::CompRender>(enemy1.get(), enemy1->transform, cameraComp, textureShader, testTexture, 1.5f,1.5f, true);
	Rev::CompCollision& enemy1Coll = *enemy1->addComponent<Rev::CompCollision>(enemy1.get(), physicsHandle, false, false, glm::vec3{0.3f, 1, 0.1f});
	enemy1Coll.SetOnContactFunction(lambdaCollEnemy);

	std::unique_ptr<Rev::GameObject> enemy2 = std::make_unique<Rev::GameObject>("Enemy2");
	enemy2->addComponent<LookAtPlayerComp>(enemy2.get(), playerTransform);
	enemy2->transform->SetPosition(5, 0, 5);
	enemy2->addComponent<Rev::CompRender>(enemy2.get(), enemy2->transform, cameraComp, textureShader, testTexture, 1.5f, 1.5f, true);
	Rev::CompCollision& enemy2Coll = *enemy2->addComponent<Rev::CompCollision>(enemy2.get(), physicsHandle, false, false, glm::vec3{ 0.3f, 1, 0.1f });
	enemy2Coll.SetOnContactFunction(lambdaCollEnemy);

	//Scene add gameobects & return
	{
		scene->addGameObject(std::move(enemy2));
		scene->addGameObject(std::move(enemy1));
		scene->addGameObject(std::move(gun));
		scene->addGameObject(std::move(player));
		for (auto&& floor : floors)
		{
			scene->addGameObject(std::move(floor));
		}
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