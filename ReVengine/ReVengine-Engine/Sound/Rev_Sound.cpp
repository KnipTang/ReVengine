#include "Rev_Sound.H"

Rev::Rev_Sound()
{
	pSoLoud = std::make_unique<Rev_SoLoud>;
}

Rev::~Rev_Sound()
{

}