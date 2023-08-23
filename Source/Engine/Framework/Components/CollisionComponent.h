#pragma once
#include "Framework/Components/Component.h"
namespace kiko
{
	class CollisionComponent : public Component
	{
	public:
		virtual bool CheckCollision(CollisionComponent* collision) = 0;
		void SetRadius(float radius) { m_radius = radius; }
		float GetRadius() { return m_radius; }
	protected:
		float m_radius = 0;
	};
}