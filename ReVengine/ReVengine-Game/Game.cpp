#include <SDL.h>
#if _DEBUG
#endif

#include "ReVengine.h"
#include <iostream>

void Load()
{
	std::cout << "t\n";
}

void PlaySound()
{
	
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