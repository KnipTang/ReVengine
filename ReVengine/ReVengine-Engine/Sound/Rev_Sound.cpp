#include "Rev_Sound.h"
#include "Rev_SoundImpl.h"
#include <iostream>

using namespace Rev;

Rev_Sound::Rev_Sound() :
	pSoundImpl{ std::make_unique<RevDev::Rev_SoundImpl>() }
{

}

Rev_Sound::~Rev_Sound()
{

}

bool Rev_Sound::PlaySound(const std::string source)
{
	return pSoundImpl->PlaySound(source);
}

