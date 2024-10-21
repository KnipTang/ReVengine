#pragma once

#include "SoLoud/Rev_SoLoud.h"
#include <memory>
#include <string>

namespace Rev
{
	class Rev_Sound
	{
	public:
		Rev_Sound();
		~Rev_Sound();

		bool PlaySound(const std::string source);
	
	private:
		bool FileValid(const std::string source);

		std::unique_ptr<RevDev::Rev_SoLoud> pSoLoud;
	};
}