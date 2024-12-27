#include "Physics.h"
#include "PhysicsImpl.h"

using namespace Rev;

Physics::Physics() :
    m_PhysicsImpl{ std::make_unique<RevDev::PhysicsImpl>() }
{
}

Physics::~Physics()
{

}

void Physics::Init()
{
    m_PhysicsImpl->Init();
}

void Physics::Simulate(float fixedDeltaTime)
{
    m_PhysicsImpl->Simulate(fixedDeltaTime);
}