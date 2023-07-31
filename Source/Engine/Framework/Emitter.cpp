#include "Emitter.h"

void kiko::Emitter::Update(float dt)
{
	Actor::Update(dt);
	// Create Burst Particles
	if (m_data.burst)
	{
		m_data.burst = false;
		for (int i = 0; i < m_data.burstCount; i++)
		{
			Emit();
		}
	}
	// Create Particles Based On Rate
	if (m_data.spawnRate > 0.0f)
	{
		m_data.spawnRateTimer += dt;
		while (m_data.spawnRateTimer > 0)
		{
			Emit();
			m_data.spawnRateTimer -= (1 / m_data.spawnRate);
		}
	}
}

void kiko::Emitter::Draw(kiko::Renderer& rend)
{
}

void kiko::Emitter::Emit()
{
	Particle* particle = g_partSys.GetFreeParticle();
	if (particle)
	{
		ParticleData data;
		data.lifeTime = randomf(m_data.lifetimeMin, m_data.lifetimeMax);
		data.lifeTimer = 0.0f;
		data.position = m_transform.position;
		data.prevPosition = data.position;
		data.color = m_data.color;

		float angle = m_transform.rotation + m_data.angle + randomf(-m_data.angleRange, m_data.angleRange);
		Vector2 direction = Vector2{ 0,-1 }.Rotate(angle);
		data.velocity = direction * randomf(m_data.speedMin, m_data.speedMax);
		data.damping = m_data.damping;
		particle->Initialize(data);
	}
}
void kiko::Emitter::EmitAtMouse(const Vector2& pos)
{
	Particle* particle = g_partSys.GetFreeParticle();
	if (particle)
	{
		ParticleData data;
		data.lifeTime = randomf(m_data.lifetimeMin, m_data.lifetimeMax);
		data.lifeTimer = 0.0f;
		data.position = pos;
		data.prevPosition = data.position;
		data.color = m_data.color;

		float angle = m_transform.rotation + m_data.angle + randomf(m_data.angleRange, m_data.angleRange);
		Vector2 direction = Vector2{ 0,-1 }.Rotate(angle);
		data.velocity = direction * randomf(m_data.speedMin, m_data.speedMax);
		data.damping = m_data.damping;
		particle->Initialize(data);
	}
}