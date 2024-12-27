#pragma once

#include <PxPhysicsAPI.h>
#include <glm/vec3.hpp>
#include <memory>

namespace RevDev
{
	class CollisionCallback;
}

namespace RevDev
{
	class Physics_PhysX
	{
	public:
		Physics_PhysX();
		~Physics_PhysX();

		void Init();
		void Simulate(float fixedDeltaTime);

		void CreateStatic(glm::vec3 pos, glm::vec3 size);
		void CreateDynamic(glm::vec3 pos, glm::vec3 size, bool gravity);
	public:
		physx::PxScene* gScene = nullptr;

	private:
		physx::PxDefaultAllocator gAllocator;
		physx::PxDefaultErrorCallback gErrorCallback;
		physx::PxFoundation* gFoundation = nullptr;
		physx::PxPhysics* gPhysics = nullptr;
		physx::PxDefaultCpuDispatcher* gDispatcher = nullptr;
		physx::PxMaterial* gMaterial = nullptr;

		physx::PxPvd* gPvd = nullptr;

	};
}