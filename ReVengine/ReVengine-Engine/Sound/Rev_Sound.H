#pragma once

#include "SoLoud/Rev_SoLoud.h"
#include <memory>

namespace Rev
{
	class Rev_Sound
	{
	public:
		Rev_Sound();
		~Rev_Sound();
	
	private:
		std::unique_ptr<RevDev::Rev_SoLoud> pSoLoud;
	};
}