#include "Game.h"
#include <iostream>
#include "RevEngine.h"
#include "soloud.h"
#include <soloud_wav.h>

int main()
{
	CmakeTestFunction();

	gSoloud.init();

	gWave.load("../resources/pew_pew.wav");

	//gSoloud.play(gWave);

	//gSoloud.deinit();
}

void GameNamNam() {
	std::cout << "miauw";
}

void PlaySound()
{
	
}