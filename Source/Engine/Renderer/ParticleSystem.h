#pragma once
#include "Core/Core.h"
#include "Renderer.h"
#include "Particle.h"

namespace kiko
{
	class ParticleSystem
	{
	public:
		ParticleSystem() = default;
		ParticleSystem(int maxCount)
		{
			m_particles.resize(maxCount);
		}
		void Update(float dt);
		void Draw(Renderer& rend);
		Particle* GetFreeParticle();
	private:
		std::vector<Particle> m_particles;

	};
	extern class ParticleSystem g_partSys;
}