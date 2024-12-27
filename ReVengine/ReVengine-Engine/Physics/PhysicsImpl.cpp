#include "PhysicsImpl.h"
#include "PhysX/Physics_PhysX.h"

using namespace RevDev;

PhysicsImpl::PhysicsImpl() :
    m_PhysicsPhysX{std::make_unique<RevDev::Physics_PhysX>()}
{
}

PhysicsImpl::~PhysicsImpl()
{

}

void PhysicsImpl::Init()
{
    m_PhysicsPhysX->Init();
}

void PhysicsImpl::Simulate(float fixedDeltaTime)
{
    m_PhysicsPhysX->Simulate(fixedDeltaTime);
}

void PhysicsImpl::CreateStatic(glm::vec3 pos, glm::vec3 size)
{
    m_PhysicsPhysX->CreateStatic(pos, size);
}

void PhysicsImpl::CreateDynamic(glm::vec3 pos, glm::vec3 size, bool gravity)
{
    m_PhysicsPhysX->CreateDynamic(pos, size, gravity);
}