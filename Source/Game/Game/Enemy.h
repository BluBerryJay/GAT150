#pragma once
#include "Framework/Framework.h"
#include "Framework/Components/PhysicsComponent.h"

namespace kiko
{
	class Enemy : public Actor
	{
	public:
		CLASS_DECLARATION(Enemy);
		Enemy() {}
		bool Initialize() override;
		void Update(float dt) override;
		void OnCollisionEnter(Actor* other) override;
		//bool 

	private:
		float m_speed = 0;
		float m_turnRate = 0;

		PhysicsComponent* m_phsyicsComponent = nullptr;
	};
}