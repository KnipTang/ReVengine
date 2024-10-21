#include "ReVengine.h"
#include "Sound/Rev_Sound.h"

using namespace Rev;

ReVengine::ReVengine(int windowWidth, int windowHeight)
{
	pRenderWindow = std::make_unique<RevDev::RenderWindow>(windowWidth, windowHeight);


	//Core systems
	pRevSound = std::make_unique<Rev::Rev_Sound>();
}

ReVengine::~ReVengine()
{
}

void ReVengine::Run(const std::function<void()>& GameRun)
{
	GameRun();

	pRenderWindow->InitWindow();

	while (true)
	{

	}
}