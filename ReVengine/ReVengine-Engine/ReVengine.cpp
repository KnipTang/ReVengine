#include "ReVengine.h"
#include "Rendering/RenderWindow.h"
#include "Scenes/SceneManager.h"
#include "Rev_CoreSystems.h"

using namespace Rev;

ReVengine::ReVengine(int windowWidth, int windowHeight)
{
	width = windowWidth;
	height = windowHeight;
}

ReVengine::~ReVengine()
{

}

void ReVengine::Run(const std::function<std::unique_ptr<SceneManager>()>& GameRun)
{
	std::unique_ptr<SceneManager> sceneMan = std::move(GameRun());

	Rev_CoreSystems::pRevRender->InitWindow(width, height);

	bool quit = false;
	while (quit == false)
	{
		sceneMan.get()->update();
		sceneMan.get()->fixedUpdate();
		sceneMan.get()->render();

		quit = Rev_CoreSystems::pRevRender->UpdateWindow();
	}

	Rev_CoreSystems::pRevRender->RipWindow();
}