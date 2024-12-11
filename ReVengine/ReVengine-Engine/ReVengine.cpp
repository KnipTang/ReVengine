#include "ReVengine.h"
#include "Rendering/RenderWindow.h"
#include "Scenes/SceneManager.h"
#include "Rev_CoreSystems.h"
#include "GameSettings.h"
#include <chrono>
#include <thread>

#define MS_PER_FRAME(fps) (1000.0f / (fps))

using namespace Rev;

ReVengine::ReVengine(int windowWidth, int windowHeight, float nearZ, float farZ) :
	m_WindowWidth{ windowWidth },
	m_WindowHeight{ windowHeight }
{
	Rev_CoreSystems::pRevRender->InitWindow(m_WindowWidth, m_WindowHeight, nearZ, farZ);
}

ReVengine::~ReVengine()
{

}

void ReVengine::Run(const std::function<SceneManager*()>& GameRun)
{
	SceneManager* sceneMan = GameRun();

	auto lastTime = std::chrono::high_resolution_clock::now();
	float lag = 0.0f;

	const float fixedTimeStep = 1.0f / GameSettings::fps;

	constexpr auto targetFrameTime = std::chrono::milliseconds(static_cast<long long>(MS_PER_FRAME(GameSettings::fps)));

	bool quit = false;
	while (quit == false)
	{
		const auto currentTime = std::chrono::high_resolution_clock::now();
		const float deltaTime = std::chrono::duration<float>(currentTime - lastTime).count();
		lastTime = currentTime;
		lag += deltaTime;

		while (lag >= fixedTimeStep)
		{
			sceneMan->fixedUpdate(fixedTimeStep);
			lag -= fixedTimeStep;
		}

		sceneMan->update(deltaTime);

		sceneMan->lateUpdate(deltaTime);

		sceneMan->render();

		quit = Rev_CoreSystems::pRevRender->UpdateWindow();

		const auto sleepTime = currentTime + targetFrameTime - std::chrono::high_resolution_clock::now();
		std::this_thread::sleep_for(sleepTime);
	}

	Rev_CoreSystems::pRevRender->RipWindow();
}