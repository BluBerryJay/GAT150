#include "EnginePhysicsComponent.h"

namespace kiko
{
	void EnginePhysicsComponent::Update(float dt)
	{
		m_owner->m_transform.position += m_velocity * dt;
		m_velocity *= std::pow(1.0f - m_damping, dt);
	}

	void EnginePhysicsComponent::ApplyForce(const Vector2& force)
	{

	}

}
