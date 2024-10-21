#include <soloud.h>
#include <soloud_wav.h>

#include "Rev_SoLoud.h"

using namespace RevDev;

Rev_SoLoud::Rev_SoLoud()
{
	pRevDev_Soloud = std::make_unique<SoLoud::Soloud>();
	pRevDev_Wave = std::make_unique<SoLoud::Wav>();

	pRevDev_Soloud->init();
}

Rev_SoLoud::~Rev_SoLoud()
{
	pRevDev_Soloud->deinit();
}

void Rev_SoLoud::PlaySound(const std::string source)
{
	pRevDev_Wave->load(source.c_str());

	pRevDev_Soloud->play(*pRevDev_Wave.get());

	while (pRevDev_Soloud->getActiveVoiceCount() > 0) {
	}

	pRevDev_Soloud->deinit();
}
