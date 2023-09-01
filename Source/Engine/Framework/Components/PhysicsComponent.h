#pragma once
#include "Component.h"
#include "Core/Core.h"
namespace kiko
{
	class PhysicsComponent : public Component
	{
	public:
		virtual void Update(float dt) = 0;
		virtual void ApplyForce(const Vector2& force) = 0;
		virtual void ApplyTorque(float torque) = 0;
		virtual void SetVelocity(const vec2& velocity) { this->m_velocity = velocity; }
		virtual void SetGravityScale(float scale) {}
	public:
		Vector2 m_velocity;
		Vector2 m_acceleration;
		float m_mass = 1.0f;
		float m_damping = 0;
		
	};
}