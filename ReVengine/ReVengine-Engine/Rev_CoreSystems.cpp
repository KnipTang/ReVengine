#include "Rev_CoreSystems.h"
#include "Sound/Rev_Sound.h"

using namespace Rev;

Rev_CoreSystems::Rev_CoreSystems()
{
	pRevSound = std::make_unique<Rev_Sound>();
}

Rev_CoreSystems::~Rev_CoreSystems()
{

}
