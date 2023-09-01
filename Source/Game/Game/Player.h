#pragma once
#include "Framework/Actor.h"
#include "Framework/Components/PhysicsComponent.h"
namespace kiko
{

	class Player : public Actor
	{
	public:
		CLASS_DECLARATION(Player);
		Player() {}
		bool Initialize() override;
		void Update(float dt) override;
		void OnCollisionEnter(Actor* other) override;

	private:
		float m_speed = 0;
		float m_turnRate = 0;
		class kiko::PhysicsComponent* m_physicsComponent = nullptr;
	};
}