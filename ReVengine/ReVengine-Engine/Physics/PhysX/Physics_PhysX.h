#pragma once

#include <PxPhysicsAPI.h>

namespace RevDev
{
	class Physics_PhysX
	{
	public:
		Physics_PhysX();
		~Physics_PhysX();

		void Init();
		void Simulate(float fixedDeltaTime);

	public:
		physx::PxScene* gScene = nullptr;

	private:
		physx::PxDefaultAllocator gAllocator;
		physx::PxDefaultErrorCallback gErrorCallback;
		physx::PxFoundation* gFoundation = nullptr;
		physx::PxPhysics* gPhysics = nullptr;
		physx::PxDefaultCpuDispatcher* gDispatcher = nullptr;
		physx::PxMaterial* gMaterial = nullptr;
	};
}