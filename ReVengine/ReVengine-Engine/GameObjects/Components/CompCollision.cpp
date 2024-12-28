#include "CompCollision.h"
#include "Physics/Physics.h"
#include "Scenes/Scene.h"
#include <stdexcept>
#include "GameObjects/Components/CompTransform.h"

using namespace Rev;

int CompCollision::colliderCounter = 0;

CompCollision::CompCollision(Rev::GameObject* gameObj, Rev::Physics* physicsHandle, bool staticObject, bool gravity, glm::vec3 size, glm::vec3 pos) :
	BaseComponent(gameObj),
    m_PhysicsHandle{ physicsHandle },
    m_Size{size},
    m_ColliderID{ colliderCounter++ }
{
    m_Position = m_GameObject->transform->GetPosition() + pos;
    staticObject ? 
        m_PhysicsHandle->CreateStatic(m_ColliderID, m_Position, size) :
        m_PhysicsHandle->CreateDynamic(m_ColliderID, m_Position, size, gravity);
}