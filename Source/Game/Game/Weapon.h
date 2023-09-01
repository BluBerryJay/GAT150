#pragma once
#include "Framework/Actor.h"
#include "Framework/Components/PhysicsComponent.h"

namespace kiko
{
	class Weapon : public Actor
	{
	public:
		CLASS_DECLARATION(Weapon);
		
		void OnCollision(Actor* other);
		bool Initialize() override;
		void Update(float dt) override;
		void OnCollisionEnter(Actor* other);

	private:
		float speed = 0;
		PhysicsComponent* m_physicsComponent = nullptr;
	};

}
