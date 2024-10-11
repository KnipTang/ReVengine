#include "ReVengine.h"
#include "soloud.h"
#include <soloud_wav.h>
#include <filesystem>
#include "d3d11_1.h"

void CmakeTestFunction()
{
	std::cout << "Test has been testlled :pp" << std::endl;
}

void EnginePlaySound()
{
	SoLoud::Soloud gSoloud;
	SoLoud::Wav gWave;

	gSoloud.init();

	std::cout << exists_test3("../resources/pew_pew.wav");

	gWave.load("../resources/pew_pew.wav");

	gSoloud.play(gWave);
	//std::cout << exists_test3("../resources/pew_pew.wav");
	//gSoloud.deinit();
}

inline bool exists_test3(const std::string& name) {
	struct stat buffer;
	return (stat(name.c_str(), &buffer) == 0);
}