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
		transform.position += forward * speed * g_time.GetDeltaTime();
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
		auto collisionComponent = GetComponent<CollisionComponent>();
		if (collisionComponent)
		{
			auto renderComponent = GetComponent<RenderComponent>();
			if (renderComponent)
			{
				float scale = transform.scale;
				collisionComponent->SetRadius(renderComponent->GetRadius() * scale);
			}
			//collisionComponent->SetRadius(GetComponent<RenderComponent>()->GetRadius());
			return true;
		}
	}

	void Weapon::OnCollision(Actor* other)
	{
		if (other->tag != tag)
	{
			destroyed = true;
		}
	}
}
