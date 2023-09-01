#include "Weapon.h"
#include "Renderer/Renderer.h"
#include "Framework/Framework.h"

namespace kiko
{
	CLASS_DEFINITION(Weapon);
	void Weapon::Update(float dt)
	{
		Actor::Update(dt);
		vec2 forward = vec2{ 0, -1 }.Rotate(transform.rotation);
		m_physicsComponent->SetVelocity(forward * speed);

		
		transform.position.x = Wrap(transform.position.x, (float)g_renderer.GetWidth());
		transform.position.y = Wrap(transform.position.y, (float)g_renderer.GetHeight());
	}
	void Weapon::Read(const json_t& value)
	{
		Actor::Read(value);

		READ_DATA(value, speed);

	}
	bool Weapon::Initialize()
	{
		Actor::Initialize();
		m_physicsComponent = GetComponent<PhysicsComponent>();
		auto collisionComponent = GetComponent<CollisionComponent>();

		if (collisionComponent)
		{
			
			
		}
		return true;
	}

	void Weapon::OnCollisionEnter(Actor* other)
	{
		if (other->tag != tag)
	{
			destroyed = true;
		}
	}
}
