#include "Model.h"
#include "Core/FileIO.h"
#include <sstream>

namespace kiko 
{
	void Model::Draw(Renderer& renderer, const Vector2& position, float rotation, float scale) 
	{
		if (m_points.empty()) return;

		renderer.SetColor(Color::ToInt(m_color.r), Color::ToInt(m_color.g), Color::ToInt(m_color.b), Color::ToInt(m_color.a));
		for (int i = 0; i < (m_points.size() - 1); i++) 
		{
			Vector2 p1 = (m_points[i] * scale).Rotate(rotation) + position;
			Vector2 p2 = (m_points[i + 1] * scale).Rotate(rotation) + position;
			renderer.DrawLine(p1.x, p1.y, p2.x, p2.y);


		}
		
	}
	void Model::Draw(Renderer& renderer, const Transform& trans)
	{
		Draw(renderer, trans.position, trans.rotation, trans.scale);
	}
	float Model::GetRadius()
	{
		if (m_radius != 0) return m_radius;

		for (auto point : m_points) 
		{
			float length = point.Length();
			m_radius = Max(m_radius, length);

		}

		return m_radius;
	}
	bool Model::Load(std::string fileName)
	{
		std::string buffer;
		kiko::readFile(fileName, buffer);
		std::istringstream stream(buffer);
		// Read Color
		stream >> m_color;

		// Read number of points
		std::string line;
		std::getline(stream, line);

		int numPoints = std::stoi(line);
		// Read Vector2 points
		for (int i = 0; i < numPoints; i++) {
			Vector2 point;
			stream >> point;
			m_points.push_back(point);
		}
		return true;
	}
}