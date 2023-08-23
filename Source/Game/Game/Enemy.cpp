#include "Enemy.h"
#include "Player.h"
#include "SpaceGame.h"
#include "Framework/Framework.h"
#include "Renderer/Renderer.h"

bool Enemy::Initialize()
{
	Actor::Initialize();
	
	auto collisionComponent = GetComponent<kiko::CollisionComponent>();
	if (collisionComponent)
	{
		auto renderComponent = GetComponent<kiko::RenderComponent>();
		if (renderComponent)
		{
			float scale = transform.scale;
			collisionComponent->SetRadius(renderComponent->GetRadius() * scale);
		}
		collisionComponent->SetRadius(GetComponent<kiko::RenderComponent>()->GetRadius());
	}
	return true;
}
void Enemy::Update(float dt)
{
	Actor::Update(dt);

	kiko::vec2 forward = kiko::vec2{ 0, -1 }.Rotate(transform.rotation);
	Player* player = m_scene->GetActor<Player>();
	if (player)
	{
		kiko::vec2 direction = player->transform.position - transform.position;
		// turn towards player		
		float turnAngle = kiko::vec2::SignedAngle(forward, direction.Normalized());
		transform.rotation += turnAngle * dt;
		// check if player is in front
		if (std::fabs(turnAngle) < kiko::DegreesToRadians(30.0f))
		{
			// I see you!
		}

	}

	transform.position += forward * m_speed * kiko::g_time.GetDeltaTime();
	transform.position.x = kiko::Wrap(transform.position.x, (float)kiko::g_renderer.GetWidth());
	transform.position.y = kiko::Wrap(transform.position.y, (float)kiko::g_renderer.GetHeight());


}

void Enemy::OnCollision(Actor* other)
{
	if (other->tag == "Player")
	{
		kiko::EventManager::Instance().DispatchEvent("AddPoints", 100);
		//m_game->AddPoints(100);
		destroyed = true;

		// create explosion
		kiko::EmitterData data;
		data.burst = true;
		data.burstCount = 100;
		data.spawnRate = 0;
		data.angle = 0;
		data.angleRange = kiko::Pi;
		data.lifetimeMin = 0.5f;
		data.lifetimeMin = 1.5f;
		data.speedMin = 50;
		data.speedMax = 250;
		data.damping = 0.5f;

		data.color = kiko::Color{ 1, 1, 1, 1 };

		kiko::Transform transform{ this->transform.position, 0, 1};
		auto emitter = std::make_unique<kiko::Emitter>(transform, data);
		emitter->lifespan = 0.1f;
		m_scene->Add(std::move(emitter));

	}
}
