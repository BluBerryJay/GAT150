#pragma once
#include "Framework/Components/CollisionComponent.h"
#include "Framework/Actor.h"
#include "Framework/Factory.h"
namespace kiko
{
	class CircleCollisionComponent : public CollisionComponent
	{
	public:
		CLASS_DECLARATION(CircleCollisionComponent)
	private:
		// Inherited via CollisionComponent
		virtual void Update(float dt) override;
		virtual bool CheckCollision(CollisionComponent* collision) override;
	};
}