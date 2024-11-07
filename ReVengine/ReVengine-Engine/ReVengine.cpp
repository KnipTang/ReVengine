#include "ReVengine.h"
#include "Rendering/RenderWindow.h"
#include "Scenes/SceneManager.h"

using namespace Rev;

ReVengine::ReVengine(int windowWidth, int windowHeight)
{
	pRenderWindow = std::make_unique<RevDev::RenderWindow>(windowWidth, windowHeight);
}

ReVengine::~ReVengine()
{

}

void ReVengine::Run(const std::function<std::unique_ptr<SceneManager>()>& GameRun)
{
	std::unique_ptr<SceneManager> sceneMan = std::move(GameRun());

	pRenderWindow->InitWindow();

	bool quit = false;
	while (quit == false)
	{
		sceneMan.get()->update();
		sceneMan.get()->fixedUpdate();
		sceneMan.get()->render();

		quit = pRenderWindow->LoopWindow();
	}

	pRenderWindow->RipWindow();
}