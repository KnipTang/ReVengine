#pragma once

#include <memory>
#include <string>

namespace RevDev {
	class Rev_SoLoud;
}

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