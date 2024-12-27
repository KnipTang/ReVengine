#include "Physics.h"
#include "PhysicsImpl.h"

using namespace Rev;

Physics::Physics()
{
    Init();
}

void Physics::Init()
{
    m_PhysicsImpl->Init();
}