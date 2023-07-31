#pragma once
#include "Core/Core.h"
#include "Renderer/Renderer.h"

namespace kiko
{
	struct ParticleData
	{
		Vector2 position;
		Vector2 prevPosition;
		Vector2 velocity;
		float damping = 0;

		Color color;

		float lifeTimer = 0;
		float lifeTime = 0;
	};
	
	class Particle
	{
	public:
		Particle() = default;
		void Initialize(const ParticleData& data)
		{
			m_data = data;
			m_isActive = true;
		}
		void Update(float dt);
		void Draw(Renderer& rend);
		friend class ParticleSystem;
	private:
		ParticleData m_data;
		bool m_isActive = false;
	};
}
