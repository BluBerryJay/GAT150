#pragma once
#include "CollisionComponent.h"
#include "Phsyics/PhysicsSystem.h"
#include <functional>

namespace kiko
{
	class Box2DCollisionComponent : public CollisionComponent
	{
	public:
		using collisionFunction = std::function<void(Actor*)>;

	public:
		CLASS_DECLARATION(Box2DCollisionComponent)

		virtual bool Initialize() override;
		virtual void Update(float dt) override;

		PhysicsSystem::CollisionData data;
	private:
		vec2 scaleOffset = vec2{ 1, 1 };
	};
}