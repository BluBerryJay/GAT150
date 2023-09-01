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
		void OnCollisionExit(Actor* other) override;

	private:
		float lives = 0;
		float speed = 0;
		float maxSpeed = 0;
		float jump = 0;
		int groundCount = 0;
		
		class PhysicsComponent* m_physicsComponent = nullptr;
		class SpriteAnimComponent* m_spriteAnimComponent = nullptr;
	};
}