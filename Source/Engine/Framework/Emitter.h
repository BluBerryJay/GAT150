#pragma once
#include "Core/Core.h"
#include "Framework/Actor.h"
#include "Renderer/Particle.h"
#include "Renderer/ParticleSystem.h"
namespace kiko
{
	struct EmitterData
	{
		float spawnRate = 0;
		float spawnRateTimer = 0;
		bool burst = false;
		size_t burstCount = 0;

		float lifetimeMin = 0;
		float lifetimeMax = 0;
		float speedMin = 0;
		float speedMax = 0;
		float damping = 0;
		float angle = 0;
		float angleRange = 0;
		Color color;
	};
	class Emitter : public Actor
	{
	public:
		Emitter() = default;
		Emitter(const Transform& trans, const EmitterData& data) :
			Actor{ trans },
			m_data{ data }
		{}
		void Update(float dt);
		void Draw(kiko::Renderer& rend);
		friend class Particle;
		friend class ParticleSystem;


	private:
		void EmitAtMouse(const Vector2& pos);
		void Emit();
	private:
		EmitterData m_data;

	};
}