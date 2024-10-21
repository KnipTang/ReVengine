#include <SDL.h>

#include "ReVengine.h"
#include "Sound/Rev_Sound.H"

#include "filesystem"
#include "iostream"

std::unique_ptr<Rev::ReVengine> gReVengine;

void displayCurrentFiles(std::string path)
{
	for (const auto& entry : std::filesystem::directory_iterator(path))
		std::cout << entry.path() << std::endl;
}

void Load()
{
	const std::string resourceFolder = "../game_resources";
	const std::string soundFolder = "/sound";
	const std::string sound_pewpew = "/pew_pew.wav";

	gReVengine->pRevSound->PlaySound(resourceFolder + soundFolder + sound_pewpew);
}

int main(int argc, char* argv[])
{
	int windowWidth = 700;
	int windowHeight = 500;

	gReVengine = std::make_unique<Rev::ReVengine>(windowWidth, windowHeight);

	gReVengine->Run(Load);

	return 0;
}