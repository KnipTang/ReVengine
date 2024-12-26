#pragma once

#include "GameObjects/BaseComponent.h"
#include <PxPhysicsAPI.h>

namespace Rev
{
	class CompCollision : public BaseComponent
	{
	public:
		CompCollision(GameObject* gameObj);
		~CompCollision() = default;

		void fixedUpdate([[maybe_unused]] float deltaTime) override;
	private:
		physx::PxDefaultAllocator gAllocator;
		physx::PxDefaultErrorCallback gErrorCallback;
		physx::PxFoundation* gFoundation = nullptr;
		physx::PxPhysics* gPhysics = nullptr;
		physx::PxDefaultCpuDispatcher* gDispatcher = nullptr;
		physx::PxScene* gScene = nullptr;
		physx::PxMaterial* gMaterial = nullptr;
	};
}