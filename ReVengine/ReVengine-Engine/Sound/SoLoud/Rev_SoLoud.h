#pragma once
#include <memory>
#include <string>

namespace SoLoud {
	class Soloud;
	class Wav;
}

namespace RevDev
{
	class Rev_SoLoud
	{
	public:
		Rev_SoLoud();
		~Rev_SoLoud();

		void PlaySound(const std::string source);

	private:
		std::unique_ptr<SoLoud::Soloud> pRevDev_Soloud;
		std::unique_ptr<SoLoud::Wav> pRevDev_Wave;
	};
}