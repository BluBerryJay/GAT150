#pragma once
#include "../Core/Core.h"
#include "Renderer.h"
#include <vector>

namespace kiko 
{
	class Model 
	{
	public:

		Model() = default;
		Model(const std::vector<Vector2> points) : m_points{ points } {}
		void Draw(Renderer& renderer, const Vector2& position, float rotation, float scale);
		void Draw(Renderer& renderer, const Transform& trans);
		float GetRadius();
		bool Load(std::string fileName);
	private:
		std::vector<Vector2> m_points;
		Color m_color;
		float m_radius = 0;

	};
}