#include "PhysicsImpl.h"
#include "PhysX/Physics_PhysX.h"

using namespace RevDev;

PhysicsImpl::PhysicsImpl() :
    m_PhysicsPhysX{std::make_unique<RevDev::Physics_PhysX>()}
{
    Init();
}

PhysicsImpl::~PhysicsImpl()
{

}

void PhysicsImpl::Init()
{
    m_PhysicsPhysX->Init();
}