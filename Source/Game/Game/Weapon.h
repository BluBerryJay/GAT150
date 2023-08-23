#pragma once
#include "Framework/Actor.h"

namespace kiko
{
	class Weapon : public Actor
	{
	public:
		CLASS_DECLARATION(Weapon);
		
		void OnCollision(Actor* other);
		bool Initialize() override;
		void Update(float dt) override;
		

	private:
		float speed = 0;
	};

}
