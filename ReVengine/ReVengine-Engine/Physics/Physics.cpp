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

void Physics::CreateStatic(glm::vec3 pos, glm::vec3 size)
{
    m_PhysicsImpl->CreateStatic(pos, size);
}

void Physics::CreateDynamic(glm::vec3 pos, glm::vec3 size, bool gravity)
{
    m_PhysicsImpl->CreateDynamic(pos, size, gravity);
}