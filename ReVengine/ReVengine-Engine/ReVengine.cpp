#include "ReVengine.h"

using namespace Rev;

ReVengine::ReVengine(int windowWidth, int windowHeight)
{
	pRenderWindow = std::make_unique<RevDev::RenderWindow>(windowWidth, windowHeight);
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