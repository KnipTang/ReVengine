#include <SDL.h>

#include "ReVengine.h"
#include "Rev_CoreSystems.h"
#include "Sound/Rev_Sound.H"

void Load()
{
	const std::string resourceFolder = "../game_resources";
	const std::string soundFolder = "/sound";
	const std::string sound_pewpew = "/pew_pew.wav";

	Rev::Rev_CoreSystems::pRevSound->PlaySound(resourceFolder + soundFolder + sound_pewpew);
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