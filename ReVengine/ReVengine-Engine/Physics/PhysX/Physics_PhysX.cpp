#include "Physics_PhysX.h"
#include "CollisionCallback.h"
#include <stdexcept>

using namespace RevDev;

Physics_PhysX::Physics_PhysX()
{
}

Physics_PhysX::~Physics_PhysX()
{
    gScene->release();
    gDispatcher->release();
    gPhysics->release();
    gFoundation->release();
}

void Physics_PhysX::Init()
{
    gFoundation = PxCreateFoundation(PX_PHYSICS_VERSION, gAllocator, gErrorCallback);
    if (!gFoundation)
        throw std::runtime_error("gFoundation error!");

    gPvd = PxCreatePvd(*gFoundation);
    physx::PxPvdTransport* transport = physx::PxDefaultPvdSocketTransportCreate("127.0.0.1", 5425, 10);
    gPvd->connect(*transport, physx::PxPvdInstrumentationFlag::eALL);

    gPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *gFoundation, physx::PxTolerancesScale(), true, gPvd);
    if (!gPhysics)
        throw std::runtime_error("gPhysics error!");

    gDispatcher = physx::PxDefaultCpuDispatcherCreate(2);

    physx::PxSceneDesc sceneDesc(gPhysics->getTolerancesScale());
    sceneDesc.gravity = physx::PxVec3(0.0f, -9.81f, 0.0f);
    sceneDesc.cpuDispatcher = gDispatcher;
    sceneDesc.filterShader = physx::PxDefaultSimulationFilterShader;
    gScene = gPhysics->createScene(sceneDesc);

    sceneDesc.flags |= physx::PxSceneFlag::eENABLE_ACTIVE_ACTORS;

    gMaterial = gPhysics->createMaterial(0.5f, 0.5f, 0.6f);
    if (!gMaterial)
        throw std::runtime_error("gMaterial error!");
    
    RevDev::CollisionCallback collisionCallback;
    gScene->setSimulationEventCallback(&collisionCallback);
}

void Physics_PhysX::Simulate(float fixedDeltaTime)
{
    gScene->simulate(fixedDeltaTime);
    gScene->fetchResults(true);
}

void Physics_PhysX::CreateStatic(glm::vec3 pos, glm::vec3 size)
{
    physx::PxTransform PxPos(physx::PxVec3(pos.x, pos.y, pos.z));
    physx::PxRigidStatic* PxStatic = gPhysics->createRigidStatic(PxPos);

    physx::PxShape* PxShape = physx::PxRigidActorExt::createExclusiveShape(*PxStatic, physx::PxBoxGeometry(size.x, size.y, size.z), *gMaterial);
    if (!PxShape)
        throw std::runtime_error("CreateExclusiveShape failed!");

    gScene->addActor(*PxStatic);
}

void Physics_PhysX::CreateDynamic(glm::vec3 pos, glm::vec3 size, bool gravity)
{
    physx::PxTransform PxPos(physx::PxVec3(pos.x, pos.y, pos.z));
    physx::PxRigidDynamic* PxDynamic = gPhysics->createRigidDynamic(PxPos);

    physx::PxShape* PxShape = physx::PxRigidActorExt::createExclusiveShape(*PxDynamic, physx::PxBoxGeometry(size.x, size.y, size.z), *gMaterial);
    if (!PxShape)
        throw std::runtime_error("CreateExclusiveShape failed!");

    if(!gravity)
        PxDynamic->setActorFlag(physx::PxActorFlag::eDISABLE_GRAVITY, true);

    physx::PxRigidBodyExt::updateMassAndInertia(*PxDynamic, 1.0f);

    gScene->addActor(*PxDynamic);
}
