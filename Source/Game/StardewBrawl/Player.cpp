#include "Player.h"
#include "Framework/Framework.h"
#include "Audio/AudioSystem.h"
#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"
#include "Renderer/Texture.h"
namespace kiko
{
	CLASS_DEFINITION(Player);

	bool Player::Initialize()
	{
		Actor::Initialize();
		// cache off
		m_physicsComponent = GetComponent<PhysicsComponent>();
		m_spriteAnimComponent = GetComponent<SpriteAnimComponent>();
		
		return true;
	}
	void Player::Update(float dt)
	{
		Actor::Update(dt);

		// movement
		bool onGround = (groundCount > 0);
		vec2 velocity = m_physicsComponent->m_velocity;
		float dir = 0;
		if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_A)) dir = -1;
		if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_D)) dir = 1;
		

		if (dir != 0)
		{
			
			velocity.x += speed * dir * ((onGround) ? 1 : 0.25f) * dt;
			velocity.x = Clamp(velocity.x, -maxSpeed, maxSpeed);
			m_physicsComponent->SetVelocity(velocity);

		}
		// jump
		if (onGround &&
			kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE) &&
			!kiko::g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_SPACE))
		{
			g_audioSystem.PlayOneShot("jumpSound");
			
			kiko::vec2 up = kiko::vec2{ 0, -1 };
			m_physicsComponent->SetVelocity(velocity + (up * jump));
		}
		if (velocity.y > 0) m_physicsComponent->SetGravityScale(3);
		else m_physicsComponent->SetGravityScale(2);
		// animation
		if (std::fabs(velocity.x) > 0.2f)
		{
			m_spriteAnimComponent->flipH = (velocity.x < -0.1f);
			m_spriteAnimComponent->SetSequence("playerRight");


		}
		else
		{
			m_spriteAnimComponent->SetSequence("playerIdle");
		}
	}

	void Player::OnCollisionEnter(Actor* other)
	{
		if (other->tag == "Enemy")
		{
			lives--;
			if (lives <= 0)
			{
				destroyed = true;
			}
			kiko::g_audioSystem.PlayOneShot("hitSound", false);
			
			
		}
		if (other->tag == "Ground") groundCount++;
		if (other->tag == "Coin")
		{
			other->destroyed = true;
			lives++;
			g_audioSystem.PlayOneShot("coinCollect", false);
		}
		if (other->tag == "Foliage")
		{
			if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_A) && !kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_A) 
				|| kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_D) && !kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_D)) g_audioSystem.PlayOneShot("bushSounds", false);
			
		}
	}
	void Player::OnCollisionExit(Actor* other)
	{
		if (other->tag == "Ground") groundCount--;
	}
	void Player::Read(const json_t& value)
	{
		Actor::Read(value);
		READ_NAME_DATA(value, "speed", speed);
		READ_NAME_DATA(value, "lives", lives);
		READ_NAME_DATA(value, "maxSpeed", maxSpeed);
		READ_NAME_DATA(value, "jump", jump);
	}
}