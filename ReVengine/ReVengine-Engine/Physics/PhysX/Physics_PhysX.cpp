#include "Physics_PhysX.h"
#include <stdexcept>

using namespace RevDev;

Physics_PhysX::Physics_PhysX()
{
}

Physics_PhysX::~Physics_PhysX()
{

}

void Physics_PhysX::Init()
{
    gFoundation = PxCreateFoundation(PX_PHYSICS_VERSION, gAllocator, gErrorCallback);
    if (!gFoundation)
        throw std::runtime_error("gFoundation error!");

    gPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *gFoundation, physx::PxTolerancesScale::PxTolerancesScale());
    if (!gPhysics)
        throw std::runtime_error("gPhysics error!");

    gDispatcher = physx::PxDefaultCpuDispatcherCreate(2);

    physx::PxSceneDesc sceneDesc(gPhysics->getTolerancesScale());
    sceneDesc.gravity = physx::PxVec3(0.0f, -9.81f, 0.0f);
    sceneDesc.cpuDispatcher = gDispatcher;
    sceneDesc.filterShader = physx::PxDefaultSimulationFilterShader;
    gScene = gPhysics->createScene(sceneDesc);

    gMaterial = gPhysics->createMaterial(0.5f, 0.5f, 0.6f);
    if (!gMaterial)
        throw std::runtime_error("gMaterial error!");
}

void Physics_PhysX::Simulate(float fixedDeltaTime)
{
    gScene->simulate(fixedDeltaTime);
    gScene->fetchResults(true);
}