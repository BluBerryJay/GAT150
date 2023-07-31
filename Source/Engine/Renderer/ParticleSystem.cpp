#include "ParticleSystem.h"

namespace kiko
{
	ParticleSystem g_partSys(1000);

	void kiko::ParticleSystem::Update(float dt)
	{
		for (auto& particle : m_particles)
		{
			if (particle.m_isActive) particle.Update(dt);

		}
	}

	void kiko::ParticleSystem::Draw(Renderer& rend)
	{
		for (auto& particle : m_particles)
		{
			if (particle.m_isActive) particle.Draw(rend);
		}
	}

	kiko::Particle* kiko::ParticleSystem::GetFreeParticle()
	{
		for (auto& particle : m_particles)
		{
			if (!particle.m_isActive) return &particle;
		}
		return nullptr;
	}

}

