#include "CircleCollisionComponent.h"

namespace kiko
{
    CLASS_DEFINITION(CircleCollisionComponent)

    void CircleCollisionComponent::Update(float dt)
    {
    }

    bool CircleCollisionComponent::CheckCollision(CollisionComponent* collision)
    {
        float distance = m_owner->transform.position.Distance(collision->GetOwner()->transform.position);
        float radius = m_radius + collision->GetRadius();
        return (distance <= radius);
    }
    void CircleCollisionComponent::Read(const json_t& value)
    {

    }
}
