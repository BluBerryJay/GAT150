#include "Enemy.h"
#include "Player.h"
#include "Framework/Framework.h"

#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"
#include "Renderer/Texture.h"
namespace kiko
{
	CLASS_DEFINITION(Enemy);

	bool Enemy::Initialize()
	{
		Actor::Initialize();
		// cache off
		m_physicsComponent = GetComponent<kiko::PhysicsComponent>();

		return true;
	}
	void Enemy::Update(float dt)
	{
		Actor::Update(dt);

		// movement
		float dir = 0;
		/*if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_A))
		{

			dir = -1;
		}
		if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_D)) dir = 1;*/

		kiko::vec2 forward = kiko::vec2{ 1, 0 };
		Player* player = m_scene->GetActor<Player>();
		if (player)
		{
			kiko::vec2 direction = player->transform.position - transform.position;
			m_physicsComponent->ApplyForce(direction.Normalized() * speed);
		}

		m_physicsComponent->ApplyForce(forward * speed * dir);
	
	}

	void Enemy::OnCollisionEnter(Actor* other)
	{
		if (other->tag == "Enemy")
		{
			kiko::EventManager::Instance().DispatchEvent("OnEnemyDead", 0);
			destroyed = true;
		}
		//if (other->tag == "Ground") groundCount++;
	}
	void Enemy::OnCollisionExit(Actor* other)
	{
		//if (other->tag == "Ground") groundCount--;
	}
	void Enemy::Read(const json_t& value)
	{
		Actor::Read(value);
		READ_NAME_DATA(value, "speed", speed);
		READ_NAME_DATA(value, "jump", jump);
	}
}