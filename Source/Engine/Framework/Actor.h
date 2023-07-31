#pragma once
#include "Core/Core.h"
#include "Renderer/Model.h"
#include <memory>
namespace kiko 
{
	class Actor
	{
	public:
		Actor() = default;
		Actor(const kiko::Transform& transform, const std::shared_ptr<Model> model) :
			m_transform{ transform },
			m_model{ model }
		{}
		Actor(const kiko::Transform& transform) :
			m_transform{ transform }
		{}

		virtual void Update(float dt);
		virtual void Draw(kiko::Renderer& renderer);

		float GetRadius() { return (m_model) ? m_model->GetRadius() * m_transform.scale : -10000; }
		virtual void OnCollision(Actor* other) {}
		Vector2& GetPosition() {
			return m_transform.position;
		}
		
		void AddForce(const Vector2& force) { m_velocity += force; }
		void SetDamping(float damping) { m_damping = damping; }
		class Scene* m_scene = nullptr;
		
		friend class Scene;
		class Game* m_game = nullptr;
		kiko::Transform m_transform;
		std::string m_tag;
		float m_lifespan = -1.0f;

		bool m_destroyed = false;
	protected:

		std::shared_ptr<Model> m_model;
		Vector2 m_velocity;
		float m_damping = 0;
	};

}
