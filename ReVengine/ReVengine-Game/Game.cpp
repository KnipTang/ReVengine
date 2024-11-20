#include "ReVengine.h"
#include "Rev_CoreSystems.h"
#include "Sound/Rev_Sound.H"
#include "GameObjects/GameObject.h"
#include "GameObjects/BaseComponent.h"
#include "GameObjects/Components/CompTransform.h"
#include "GameObjects/Components/CompRender.h"
#include "GameObjects/Components/CompInput.h"
#include "Scenes/Scene.h"
#include "Scenes/SceneManager.h"
#include "Rendering/Texture.h"

#include <SDL_scancode.h>

const std::string resourceFolder = "../game_resources";
const std::string doomSprites = "/doomSprites";
const std::string doomEnemies = "/Enemies";

void testFunction()
{
	const std::string SoundPew = "/sound/pew_pew.wav";
	Rev::Rev_CoreSystems::pRevSound->PlaySound(resourceFolder + SoundPew);
}

std::unique_ptr<Rev::Scene> Scene1()
{
	//Sound
	{
		const std::string SoundPew = "/sound/pew_pew.wav";

		Rev::Rev_CoreSystems::pRevSound->PlaySound(resourceFolder + SoundPew);
	}

	std::unique_ptr<Rev::GameObject> player = std::make_unique<Rev::GameObject>();
	std::unique_ptr<Rev::GameObject> player1 = std::make_unique<Rev::GameObject>();

	const std::string testDoomFile = resourceFolder + doomSprites + doomEnemies + "/bossb1.png";
	const std::string texturePath = testDoomFile;
	Rev::Texture* testTexture = new Rev::Texture(texturePath);

	player->addComponent<Rev::CompTransform>(player.get(), Vector3{ -2,0,-5 });
	player->addComponent<Rev::CompRender>(player.get(), player->getComponent<Rev::CompTransform>(), testTexture);
	Rev::CompInput* inputComp = player->addComponent<Rev::CompInput>(player.get());
	inputComp->BindAction(SDL_SCANCODE_E, testFunction);

	player1->addComponent<Rev::CompTransform>(player1.get(), Vector3{ 2,0,-5 });
	player1->addComponent<Rev::CompRender>(player1.get(), player1->getComponent<Rev::CompTransform>(), testTexture);



	//Scene add gameobects & return
	{
		std::unique_ptr<Rev::Scene> scene = std::make_unique<Rev::Scene>();
		scene->addGameObject(std::move(player));
		scene->addGameObject(std::move(player1));
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
	int windowWidth = 700;
	int windowHeight = 500;

	std::unique_ptr<Rev::ReVengine> pReVengine;
	pReVengine = std::make_unique<Rev::ReVengine>(windowWidth, windowHeight);

	pReVengine->Run(Load);

	return 0;
}