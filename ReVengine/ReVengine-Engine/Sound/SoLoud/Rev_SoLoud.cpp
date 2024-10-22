#include "Rev_SoLoud.h"

#include <soloud.h>
#include <soloud_wav.h>

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
}
