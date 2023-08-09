#pragma once
#include "Component.h"
#include "Core/Core.h"
namespace kiko
{
	class PhysicsComponent : public Component
	{
	public:
		virtual void Update(float dt) override;
		virtual void ApplyForce(const Vector2& force) = 0;

	public:
		Vector2 m_velocity;
		Vector2 m_acceleration;
		float m_mass = 1.0f;
		float m_damping = 0;
		
	};
}