#pragma once
#include "PhysicsComponent.h"
namespace kiko
{
	class EnginePhysicsComponent : public PhysicsComponent
	{
	public:

		// Inherited via PhysicsComponent
		virtual void ApplyForce(const Vector2& force) override;
		virtual void Update(float dt) override;
	};
}