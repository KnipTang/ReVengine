#include "Rev_Sound.H"
#include <iostream>
#include "SoLoud/Rev_SoLoud.h"

using namespace Rev;

Rev_Sound::Rev_Sound()
{
	pSoLoud = std::make_unique<RevDev::Rev_SoLoud>();
}

Rev_Sound::~Rev_Sound()
{

}

bool Rev_Sound::PlaySound(const std::string source)
{
	if (!FileValid(source))
	{
		std::cerr << "source file not found";
		return 0;
	}
	else
		pSoLoud->PlaySound(source);

	return 1;
}

bool Rev_Sound::FileValid(const std::string source)
{
	struct stat buffer;
	return (stat(source.c_str(), &buffer) == 0);
}