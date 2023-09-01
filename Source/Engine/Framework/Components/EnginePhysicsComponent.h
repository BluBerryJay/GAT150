#pragma once
#include "PhysicsComponent.h"
#include "Framework/Factory.h"
namespace kiko
{
	class EnginePhysicsComponent : public PhysicsComponent
	{
	public:
		CLASS_DECLARATION(EnginePhysicsComponent)
		// Inherited via PhysicsComponent
		virtual void ApplyForce(const Vector2& force) override;
		virtual void Update(float dt) override;

		// Inherited via PhysicsComponent
		virtual void ApplyTorque(float torque) override;
	};
}