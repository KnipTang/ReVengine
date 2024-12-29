#include "CompCollision.h"
#include "Physics/Physics.h"
#include "Scenes/Scene.h"
#include <stdexcept>
#include "GameObjects/Components/CompTransform.h"

using namespace Rev;

int CompCollision::colliderCounter = 0;

CompCollision::CompCollision(Rev::GameObject* gameObj, Rev::Physics* physicsHandle, std::function<void(Rev::CompCollision* other)> collisionFnc, bool staticObject, bool gravity, glm::vec3 size, glm::vec3 pos) :
    BaseComponent(gameObj),
    m_CollisionFnc{ collisionFnc },
    m_PhysicsHandle{ physicsHandle },
    m_TransformHandle{ m_GameObject->transform },
    m_Size{size},
    m_ColliderID{ colliderCounter++ }
{
    m_Position = m_TransformHandle->GetWorldPosition() + pos;
    staticObject ? 
        m_PhysicsHandle->CreateStatic(m_ColliderID, m_Position, size) :
        m_PhysicsHandle->CreateDynamic(m_ColliderID, m_Position, size, gravity, this);
}

CompCollision::~CompCollision()
{
    m_PhysicsHandle->DestroyCollider(m_ColliderID);
}

void CompCollision::update([[maybe_unused]] float deltaTime)
{
    //if (m_TransformHandle->IsPositionDirty() || m_TransformHandle->IsRotationDirty())
        m_PhysicsHandle->UpdateActorTransform(m_ColliderID, m_TransformHandle->GetWorldPosition(), m_TransformHandle->GetWorldRotation());
}